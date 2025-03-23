// Copyright 2025 Prince Roshan <princekrroshan01@gmail.com>

#ifndef INCLUDE_FILETYPE_TYPES_HPP_
#define INCLUDE_FILETYPE_TYPES_HPP_

/**
 * @file types.hpp
 * @brief Main header file for file type definitions
 *
 * This header serves as the central include file for all file type definitions
 * in the cpp-filetype library. It includes the common type definition as well
 * as all category-specific type headers.
 */

#include <array>
#include <cstdint>
#include <string_view>
#include <vector>

#include "filetype/type.hpp"
#include "filetype/types/archive.hpp"
#include "filetype/types/audio.hpp"
#include "filetype/types/document.hpp"
#include "filetype/types/image.hpp"
#include "filetype/types/video.hpp"

namespace filetype {

namespace types {

/**
 * @brief Check if bytes match a magic number pattern.
 *
 * @param bytes Buffer containing file data.
 * @param magic Pointer to magic number sequence.
 * @param magic_size Length of the magic number sequence.
 * @param offset Offset in bytes where to start matching (default: 0).
 * @return true if bytes match the magic number pattern.
 */
inline bool match_magic(const std::vector<uint8_t>& bytes, const uint8_t* magic,
                        size_t magic_size, size_t offset = 0);

/**
 * @brief Template version of match_magic for std::array magic numbers.
 *
 * @tparam N Size of the magic number array.
 * @param bytes Buffer containing file data.
 * @param magic Array containing magic number sequence.
 * @param offset Offset in bytes where to start matching (default: 0).
 * @return true if bytes match the magic number pattern.
 */
template <size_t N>
inline bool match_magic(const std::vector<uint8_t>& bytes,
                        const std::array<uint8_t, N>& magic,
                        size_t offset = 0) {
  return match_magic(bytes, magic.data(), N, offset);
}

/**
 * @brief Check if a buffer is valid for type detection.
 *
 * @param bytes Buffer to check.
 * @param min_size Minimum required size (default: 8 bytes).
 * @return true if buffer is valid and has sufficient size.
 */
inline bool is_valid_buffer(const std::vector<uint8_t>& bytes,
                            size_t min_size = 8);

// Import commonly used types from category namespaces

// Image types
using image::TYPE_BMP;
using image::TYPE_CR2;
using image::TYPE_GIF;
using image::TYPE_HEIC;
using image::TYPE_ICO;
using image::TYPE_JPEG;
using image::TYPE_JXR;
using image::TYPE_PNG;
using image::TYPE_PSD;
using image::TYPE_TIFF;
using image::TYPE_WEBP;

// Document types
using document::TYPE_DOC;
using document::TYPE_DOCX;
using document::TYPE_EPUB;
using document::TYPE_PDF;
using document::TYPE_PPT;
using document::TYPE_PPTX;
using document::TYPE_RTF;
using document::TYPE_XLS;
using document::TYPE_XLSX;

// Archive types
using archive::TYPE_7Z;
using archive::TYPE_BZ2;
using archive::TYPE_GZ;
using archive::TYPE_RAR;
using archive::TYPE_TAR;
using archive::TYPE_XZ;
using archive::TYPE_Z;
using archive::TYPE_ZIP;

// Audio types
using audio::TYPE_AAC;
using audio::TYPE_AIFF;
using audio::TYPE_FLAC;
using audio::TYPE_M4A;
using audio::TYPE_MIDI;
using audio::TYPE_MP3;
using audio::TYPE_OGG;
using audio::TYPE_WAV;
using audio::TYPE_WMA;

// Video types
using video::TYPE_3GP;
using video::TYPE_AVI;
using video::TYPE_FLV;
using video::TYPE_MKV;
using video::TYPE_MOV;
using video::TYPE_MP4;
using video::TYPE_MPEG;
using video::TYPE_WEBM;
using video::TYPE_WMV;

// Import magic number definitions

// Image magic numbers
using image::BMP_MAGIC;
using image::CR2_MAGIC;
using image::GIF_MAGIC;
using image::HEIC_MAGIC;
using image::ICO_MAGIC;
using image::JPEG_MAGIC;
using image::JXR_MAGIC;
using image::PNG_MAGIC;
using image::PSD_MAGIC;
using image::TIFF_MAGIC_BE;
using image::TIFF_MAGIC_LE;
using image::WEBP_MAGIC;

// Document magic numbers
using document::DOC_MAGIC;
using document::DOCX_MAGIC;
using document::PDF_MAGIC;
using document::RTF_MAGIC;

// Archive magic numbers
using archive::BZ2_MAGIC;
using archive::GZ_MAGIC;
using archive::RAR_MAGIC;
using archive::SEVEN_Z_MAGIC;
using archive::TAR_MAGIC;
using archive::XZ_MAGIC;
using archive::Z_MAGIC;
using archive::ZIP_MAGIC;

// Audio magic numbers
using audio::AAC_MAGIC;
using audio::AIFF_MAGIC;
using audio::FLAC_MAGIC;
using audio::M4A_MAGIC;
using audio::MIDI_MAGIC;
using audio::MP3_ID3_MAGIC;
using audio::MP3_MAGIC;
using audio::OGG_MAGIC;
using audio::WAV_MAGIC;
using audio::WMA_MAGIC;

// Video magic numbers
using video::AVI_MAGIC;
using video::FLV_MAGIC;
using video::MKV_MAGIC;
using video::MOV_MAGIC;
using video::MP4_MAGIC;
using video::MPEG_MAGIC;
using video::MPEG_MAGIC_ALT;
using video::THREEGP_MAGIC;
using video::WEBM_MAGIC;
using video::WMV_MAGIC;

}  // namespace types
}  // namespace filetype

#endif  // INCLUDE_FILETYPE_TYPES_HPP_
