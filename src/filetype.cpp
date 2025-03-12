#include "filetype/filetype.hpp"
#include "filetype/types/image.hpp"
#include "filetype/types/document.hpp"
#include "filetype/types/archive.hpp"
#include "filetype/types/audio.hpp"
#include "filetype/types/video.hpp"
#include <algorithm>
#include <cstring>
#include <string_view>
#include <fstream>
#include <iterator>

namespace filetype {

namespace internal {
    // Add a default value for the offset parameter.
    bool match_magic(const std::vector<uint8_t>& bytes, const uint8_t* magic, size_t length, size_t offset = 0) {
        if (bytes.size() < length + offset) {
            return false;
        }
        return std::memcmp(bytes.data() + offset, magic, length) == 0;
    }
} // namespace internal

// IMPORTANT: Ensure that your category-specific constants (e.g. image::TYPE_PNG)
// are declared as type filetype::Type (the common type) rather than a separate type.

const Type* match(const std::vector<uint8_t>& bytes) {
    if (bytes.empty()) {
        return nullptr;
    }

    // Check image formats
    if (internal::match_magic(bytes, image::PNG_MAGIC.data(), image::PNG_MAGIC.size())) {
        return &image::TYPE_PNG;
    }
    if (internal::match_magic(bytes, image::JPEG_MAGIC.data(), image::JPEG_MAGIC.size())) {
        return &image::TYPE_JPEG;
    }
    if (internal::match_magic(bytes, image::GIF_MAGIC.data(), image::GIF_MAGIC.size())) {
        return &image::TYPE_GIF;
    }
    if (internal::match_magic(bytes, image::WEBP_MAGIC.data(), image::WEBP_MAGIC.size())) {
        return &image::TYPE_WEBP;
    }
    if (internal::match_magic(bytes, image::CR2_MAGIC.data(), image::CR2_MAGIC.size())) {
        return &image::TYPE_CR2;
    }
    if (internal::match_magic(bytes, image::TIFF_MAGIC_LE.data(), image::TIFF_MAGIC_LE.size()) ||
        internal::match_magic(bytes, image::TIFF_MAGIC_BE.data(), image::TIFF_MAGIC_BE.size())) {
        return &image::TYPE_TIFF;
    }
    
    // Check document formats
    if (internal::match_magic(bytes, document::PDF_MAGIC.data(), document::PDF_MAGIC.size())) {
        return &document::TYPE_PDF;
    }
    if (internal::match_magic(bytes, document::DOC_MAGIC.data(), document::DOC_MAGIC.size())) {
        return &document::TYPE_DOC;
    }
    if (internal::match_magic(bytes, document::RTF_MAGIC.data(), document::RTF_MAGIC.size())) {
        return &document::TYPE_RTF;
    }
    
    // Check archive formats
    if (internal::match_magic(bytes, archive::ZIP_MAGIC.data(), archive::ZIP_MAGIC.size())) {
        return &archive::TYPE_ZIP;
    }
    if (internal::match_magic(bytes, archive::RAR_MAGIC.data(), archive::RAR_MAGIC.size())) {
        return &archive::TYPE_RAR;
    }
    // For TAR, the magic appears at offset 257
    if (internal::match_magic(bytes, archive::TAR_MAGIC.data(), archive::TAR_MAGIC.size(), 257)) {
        return &archive::TYPE_TAR;
    }
    
    // Check audio formats
    if (internal::match_magic(bytes, audio::MP3_MAGIC.data(), audio::MP3_MAGIC.size()) ||
        internal::match_magic(bytes, audio::MP3_ID3_MAGIC.data(), audio::MP3_ID3_MAGIC.size())) {
        return &audio::TYPE_MP3;
    }
    if (internal::match_magic(bytes, audio::WAV_MAGIC.data(), audio::WAV_MAGIC.size())) {
        return &audio::TYPE_WAV;
    }
    
    // Check video formats
    if (internal::match_magic(bytes, video::MP4_MAGIC.data(), video::MP4_MAGIC.size())) {
        return &video::TYPE_MP4;
    }
    if (internal::match_magic(bytes, video::AVI_MAGIC.data(), video::AVI_MAGIC.size())) {
        return &video::TYPE_AVI;
    }
    
    return nullptr;
}

const Type* match_file(const std::string& filepath, size_t max_read_size) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        return nullptr;
    }
    std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
    if(buffer.size() > max_read_size) {
        buffer.resize(max_read_size);
    }
    return match(buffer);
}

bool is(const std::vector<uint8_t>& bytes, const Type& type) {
    const Type* detected = match(bytes);
    if (!detected) return false;
    return std::string_view(detected->mime) == type.mime &&
           std::string_view(detected->extension) == type.extension;
}

bool is_image(const std::vector<uint8_t>& bytes) {
    const Type* type = match(bytes);
    if (!type) return false;
    return std::string_view(type->mime).substr(0, 6) == "image/";
}

bool is_document(const std::vector<uint8_t>& bytes) {
    const Type* type = match(bytes);
    if (!type) return false;
    auto mime = std::string_view(type->mime);
    return mime.substr(0, 12) == "application/" &&
           mime.substr(0, 14) != "application/x-";
}

bool is_archive(const std::vector<uint8_t>& bytes) {
    const Type* type = match(bytes);
    if (!type) return false;
    auto mime = std::string_view(type->mime);
    return mime.substr(0, 14) == "application/x-" ||
           mime == "application/zip";
}

bool is_audio(const std::vector<uint8_t>& bytes) {
    const Type* type = match(bytes);
    if (!type) return false;
    return std::string_view(type->mime).substr(0, 6) == "audio/";
}

bool is_video(const std::vector<uint8_t>& bytes) {
    const Type* type = match(bytes);
    if (!type) return false;
    return std::string_view(type->mime).substr(0, 6) == "video/";
}

namespace matcher {

const Type* match_image(const std::vector<uint8_t>& bytes) {
    const Type* t = match(bytes);
    if (t && std::string_view(t->mime).substr(0, 6) == "image/") {
        return t;
    }
    return nullptr;
}

const Type* match_document(const std::vector<uint8_t>& bytes) {
    const Type* t = match(bytes);
    if (t && std::string_view(t->mime).substr(0, 12) == "application/" &&
        std::string_view(t->mime).substr(0, 14) != "application/x-") {
        return t;
    }
    return nullptr;
}

const Type* match_archive(const std::vector<uint8_t>& bytes) {
    const Type* t = match(bytes);
    if (t && (std::string_view(t->mime).substr(0, 14) == "application/x-" ||
              std::string_view(t->mime) == "application/zip")) {
        return t;
    }
    return nullptr;
}

const Type* match_audio(const std::vector<uint8_t>& bytes) {
    const Type* t = match(bytes);
    if (t && std::string_view(t->mime).substr(0, 6) == "audio/") {
        return t;
    }
    return nullptr;
}

const Type* match_video(const std::vector<uint8_t>& bytes) {
    const Type* t = match(bytes);
    if (t && std::string_view(t->mime).substr(0, 6) == "video/") {
        return t;
    }
    return nullptr;
}

} // namespace matcher

} // namespace filetype
