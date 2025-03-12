#ifndef FILETYPE_TYPES_HPP
#define FILETYPE_TYPES_HPP

/**
 * @file types.hpp
 * @brief Main header file for file type definitions
 * 
 * This header serves as the central include file for all file type definitions
 * in the cpp-filetype library. It includes the common type definition as well as
 * all category-specific type headers.
 */

// First, include the common type header.
#include "filetype/type.hpp"

// Include all category-specific headers.
// These headers should include "filetype/type.hpp" on their own (or rely on this order).
#include "filetype/types/image.hpp"
#include "filetype/types/document.hpp"
#include "filetype/types/archive.hpp"
#include "filetype/types/audio.hpp"
#include "filetype/types/video.hpp"

#include <string>
#include <vector>
#include <array>
#include <cstdint>

namespace filetype {

// The common Type struct is now defined in "filetype/type.hpp".

namespace types {

/**
 * @brief Check if bytes match a magic number pattern
 * 
 * @param bytes Buffer containing file data
 * @param magic Pointer to magic number sequence
 * @param magic_size Length of the magic number sequence
 * @param offset Offset in bytes where to start matching (default: 0)
 * @return true if bytes match the magic number pattern
 */
bool match_magic(const std::vector<uint8_t>& bytes, 
                   const uint8_t* magic, 
                   size_t magic_size,
                   size_t offset = 0);

/**
 * @brief Template version of match_magic for std::array magic numbers
 * 
 * @tparam N Size of the magic number array
 * @param bytes Buffer containing file data
 * @param magic Array containing magic number sequence
 * @param offset Offset in bytes where to start matching (default: 0)
 * @return true if bytes match the magic number pattern
 */
template <size_t N>
bool match_magic(const std::vector<uint8_t>& bytes,
                 const std::array<uint8_t, N>& magic,
                 size_t offset = 0) {
    return match_magic(bytes, magic.data(), N, offset);
}

/**
 * @brief Check if a buffer is valid for type detection
 * 
 * @param bytes Buffer to check
 * @param min_size Minimum required size (default: 8 bytes)
 * @return true if buffer is valid and has sufficient size
 */
bool is_valid_buffer(const std::vector<uint8_t>& bytes, size_t min_size = 8);

// Import commonly used types from category namespaces
// Image types
using image::TYPE_PNG;
using image::TYPE_JPEG;
using image::TYPE_GIF;
using image::TYPE_WEBP;
using image::TYPE_CR2;
using image::TYPE_TIFF;
using image::TYPE_BMP;
using image::TYPE_JXR;
using image::TYPE_PSD;
using image::TYPE_ICO;
using image::TYPE_HEIC;

// Document types
using document::TYPE_PDF;
using document::TYPE_DOC;
using document::TYPE_DOCX;
using document::TYPE_XLS;
using document::TYPE_XLSX;
using document::TYPE_PPT;
using document::TYPE_PPTX;
using document::TYPE_RTF;
using document::TYPE_EPUB;

// Archive types
using archive::TYPE_ZIP;
using archive::TYPE_RAR;
using archive::TYPE_TAR;
using archive::TYPE_7Z;
using archive::TYPE_GZ;
using archive::TYPE_BZ2;
using archive::TYPE_XZ;
using archive::TYPE_Z;

// Audio types
using audio::TYPE_MP3;
using audio::TYPE_WAV;
using audio::TYPE_MIDI;
using audio::TYPE_FLAC;
using audio::TYPE_AAC;
using audio::TYPE_OGG;
using audio::TYPE_WMA;
using audio::TYPE_AIFF;
using audio::TYPE_M4A;

// Video types
using video::TYPE_MP4;
using video::TYPE_AVI;
using video::TYPE_MKV;
using video::TYPE_WEBM;
using video::TYPE_MOV;
using video::TYPE_FLV;
using video::TYPE_WMV;
using video::TYPE_MPEG;
using video::TYPE_3GP;

// Import magic number definitions
// Image magic numbers
using image::PNG_MAGIC;
using image::JPEG_MAGIC;
using image::GIF_MAGIC;
using image::WEBP_MAGIC;
using image::CR2_MAGIC;
using image::TIFF_MAGIC_LE;
using image::TIFF_MAGIC_BE;
using image::BMP_MAGIC;
using image::JXR_MAGIC;
using image::PSD_MAGIC;
using image::ICO_MAGIC;
using image::HEIC_MAGIC;

// Document magic numbers
using document::PDF_MAGIC;
using document::DOC_MAGIC;
using document::DOCX_MAGIC;
using document::RTF_MAGIC;

// Archive magic numbers
using archive::ZIP_MAGIC;
using archive::RAR_MAGIC;
using archive::TAR_MAGIC;
using archive::SEVEN_Z_MAGIC;
using archive::GZ_MAGIC;
using archive::BZ2_MAGIC;
using archive::XZ_MAGIC;
using archive::Z_MAGIC;

// Audio magic numbers
using audio::MP3_MAGIC;
using audio::MP3_ID3_MAGIC;
using audio::WAV_MAGIC;
using audio::MIDI_MAGIC;
using audio::FLAC_MAGIC;
using audio::AAC_MAGIC;
using audio::OGG_MAGIC;
using audio::WMA_MAGIC;
using audio::AIFF_MAGIC;
using audio::M4A_MAGIC;

// Video magic numbers
using video::MP4_MAGIC;
using video::AVI_MAGIC;
using video::MKV_MAGIC;
using video::WEBM_MAGIC;
using video::MOV_MAGIC;
using video::FLV_MAGIC;
using video::WMV_MAGIC;
using video::MPEG_MAGIC;
using video::MPEG_MAGIC_ALT;
using video::THREEGP_MAGIC;

} // namespace types

/**
 * @brief Check if file data matches a specific file type
 * 
 * @param bytes Buffer containing file data
 * @param type Type to check against
 * @return true if the data matches the specified type
 */
bool is(const std::vector<uint8_t>& bytes, const Type& type);

/**
 * @brief Check if file data is an image format
 * 
 * @param bytes Buffer containing file data
 * @return true if the data is an image format
 */
bool is_image(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file data is a document format
 * 
 * @param bytes Buffer containing file data
 * @return true if the data is a document format
 */
bool is_document(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file data is an archive format
 * 
 * @param bytes Buffer containing file data
 * @return true if the data is an archive format
 */
bool is_archive(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file data is an audio format
 * 
 * @param bytes Buffer containing file data
 * @return true if the data is an audio format
 */
bool is_audio(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file data is a video format
 * 
 * @param bytes Buffer containing file data
 * @return true if the data is a video format
 */
bool is_video(const std::vector<uint8_t>& bytes);

/**
 * @brief Detect file type from a byte buffer
 * 
 * This function attempts to detect the file type by comparing the buffer's contents
 * with known magic numbers of various file formats.
 * 
 * @param bytes Buffer containing the file data to analyze
 * @return Pointer to the detected file type, or nullptr if type could not be determined
 */
const Type* match(const std::vector<uint8_t>& bytes);

/**
 * @brief Detect file type from a file path
 * 
 * This function reads the beginning of the file and attempts to detect its type
 * by comparing with known magic numbers.
 * 
 * @param filepath Path to the file to analyze
 * @param max_read_size Maximum number of bytes to read from the file (default: 8192)
 * @return Pointer to the detected file type, or nullptr if type could not be determined
 */
const Type* match_file(const std::string& filepath, size_t max_read_size = 8192);

} // namespace filetype

#endif // FILETYPE_TYPES_HPP
