// Copyright 2025 Prince Roshan <princekrroshan01@gmail.com>

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <string_view>

#include "filetype/filetype.hpp"
#include "filetype/types/archive.hpp"
#include "filetype/types/audio.hpp"
#include "filetype/types/document.hpp"
#include "filetype/types/image.hpp"
#include "filetype/types/video.hpp"

namespace filetype {
namespace internal {
bool match_magic(const std::vector<uint8_t>& bytes, const uint8_t* magic,
size_t length, size_t offset = 0) {
if (bytes.size() < length + offset) {
return false;
}
return std::memcmp(bytes.data() + offset, magic, length) == 0;
}
}  // namespace internal

const Type* match(const std::vector<uint8_t>& bytes) {
  if (bytes.empty()) {
    return nullptr;
  }

  // Check image formats
  if (internal::match_magic(bytes, image::PNG_MAGIC.data(),
                            image::PNG_MAGIC.size())) {
    return &image::TYPE_PNG;
  }
  if (internal::match_magic(bytes, image::JPEG_MAGIC.data(),
                            image::JPEG_MAGIC.size())) {
    return &image::TYPE_JPEG;
  }
  if (internal::match_magic(bytes, image::GIF_MAGIC.data(),
                            image::GIF_MAGIC.size())) {
    return &image::TYPE_GIF;
  }
  if (internal::match_magic(bytes, image::WEBP_MAGIC.data(),
                            image::WEBP_MAGIC.size())) {
    return &image::TYPE_WEBP;
  }
  if (internal::match_magic(bytes, image::CR2_MAGIC.data(),
                            image::CR2_MAGIC.size())) {
    return &image::TYPE_CR2;
  }
  if (internal::match_magic(bytes, image::TIFF_MAGIC_LE.data(),
                            image::TIFF_MAGIC_LE.size()) ||
      internal::match_magic(bytes, image::TIFF_MAGIC_BE.data(),
                            image::TIFF_MAGIC_BE.size())) {
    return &image::TYPE_TIFF;
  }

  // Check document formats
  if (internal::match_magic(bytes, document::PDF_MAGIC.data(),
                            document::PDF_MAGIC.size())) {
    return &document::TYPE_PDF;
  }
  if (internal::match_magic(bytes, document::DOC_MAGIC.data(),
                            document::DOC_MAGIC.size())) {
    return &document::TYPE_DOC;
  }
  if (internal::match_magic(bytes, document::RTF_MAGIC.data(),
                            document::RTF_MAGIC.size())) {
    return &document::TYPE_RTF;
  }

  // Check archive formats
  if (internal::match_magic(bytes, archive::ZIP_MAGIC.data(),
                            archive::ZIP_MAGIC.size())) {
    return &archive::TYPE_ZIP;
  }
  if (internal::match_magic(bytes, archive::RAR_MAGIC.data(),
                            archive::RAR_MAGIC.size())) {
    return &archive::TYPE_RAR;
  }
  // For TAR, the magic appears at offset 257
  if (internal::match_magic(bytes, archive::TAR_MAGIC.data(),
                            archive::TAR_MAGIC.size(), 257)) {
    return &archive::TYPE_TAR;
  }

  // Check audio formats
  if (internal::match_magic(bytes, audio::MP3_MAGIC.data(),
                            audio::MP3_MAGIC.size()) ||
      internal::match_magic(bytes, audio::MP3_ID3_MAGIC.data(),
                            audio::MP3_ID3_MAGIC.size())) {
    return &audio::TYPE_MP3;
  }
  if (internal::match_magic(bytes, audio::WAV_MAGIC.data(),
                            audio::WAV_MAGIC.size())) {
    return &audio::TYPE_WAV;
  }

  // Check video formats
  if (internal::match_magic(bytes, video::MP4_MAGIC.data(),
                            video::MP4_MAGIC.size())) {
    return &video::TYPE_MP4;
  }
  if (internal::match_magic(bytes, video::AVI_MAGIC.data(),
                            video::AVI_MAGIC.size())) {
    return &video::TYPE_AVI;
  }

  return nullptr;
}

const Type* match_file(std::string_view filepath, size_t max_read_size) {
  std::ifstream file(std::string(filepath), std::ios::binary);
  if (!file) {
    std::cerr << "Error: Could not open file: " << filepath << "\n";
    return nullptr;
  }
  std::vector<uint8_t> buffer(max_read_size);
  file.read(reinterpret_cast<char*>(buffer.data()), max_read_size);
  buffer.resize(static_cast<size_t>(file.gcount()));
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
  std::string_view mime(type->mime);
  if (mime.size() < 6) return false;
  return mime.substr(0, 6) == "image/";
}

bool is_document(const std::vector<uint8_t>& bytes) {
  const Type* type = match(bytes);
  if (!type) return false;
  std::string_view mime(type->mime);
  if (mime.size() < 12) return false;
  if (mime.substr(0, 12) != "application/") return false;
  if (mime.size() >= 14 && mime.substr(0, 14) == "application/x-") return false;
  return true;
}

bool is_archive(const std::vector<uint8_t>& bytes) {
  const Type* type = match(bytes);
  if (!type) return false;
  std::string_view mime(type->mime);
  if (mime.size() < 14) return false;
  return mime.substr(0, 14) == "application/x-" || mime == "application/zip";
}

bool is_audio(const std::vector<uint8_t>& bytes) {
  const Type* type = match(bytes);
  if (!type) return false;
  std::string_view mime(type->mime);
  if (mime.size() < 6) return false;
  return mime.substr(0, 6) == "audio/";
}

bool is_video(const std::vector<uint8_t>& bytes) {
  const Type* type = match(bytes);
  if (!type) return false;
  std::string_view mime(type->mime);
  if (mime.size() < 6) return false;
  return mime.substr(0, 6) == "video/";
}

template <typename Predicate>
const Type* match_if(const std::vector<uint8_t>& bytes, Predicate pred) {
  const Type* t = match(bytes);
  return (t && pred(std::string_view(t->mime))) ? t : nullptr;
}

namespace matcher {

const Type* match_image(const std::vector<uint8_t>& bytes) {
  return match_if(bytes, [](std::string_view mime) {
    return mime.size() >= 6 && mime.substr(0, 6) == "image/";
  });
}

const Type* match_document(const std::vector<uint8_t>& bytes) {
  return match_if(bytes, [](std::string_view mime) {
    return mime.size() >= 12 && mime.substr(0, 12) == "application/" &&
           (mime.size() < 14 || mime.substr(0, 14) != "application/x-");
  });
}

const Type* match_archive(const std::vector<uint8_t>& bytes) {
  return match_if(bytes, [](std::string_view mime) {
    return (mime.size() >= 14 && mime.substr(0, 14) == "application/x-") ||
           mime == "application/zip";
  });
}

const Type* match_audio(const std::vector<uint8_t>& bytes) {
  return match_if(bytes, [](std::string_view mime) {
    return mime.size() >= 6 && mime.substr(0, 6) == "audio/";
  });
}

const Type* match_video(const std::vector<uint8_t>& bytes) {
  return match_if(bytes, [](std::string_view mime) {
    return mime.size() >= 6 && mime.substr(0, 6) == "video/";
  });
}

}  // namespace matcher

}  // namespace filetype
