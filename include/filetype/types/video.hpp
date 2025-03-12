#ifndef FILETYPE_TYPES_VIDEO_TYPES_HPP
#define FILETYPE_TYPES_VIDEO_TYPES_HPP

#include <array>
#include <cstdint>
#include <string>
#include "filetype/type.hpp"  // Include the central header where filetype::Type is defined

namespace filetype {
namespace video {

// Alias the common Type defined in filetype/types.hpp
using Type = ::filetype::Type;

//------------------------------------------------------------------------------
// Video file type definitions
//------------------------------------------------------------------------------

// MP4 video format
// Magic: 00 00 00 XX 66 74 79 70 (....ftyp)
// Common variants: iso2, iso3, iso4, isom, mp41, mp42, dash
inline const std::array<uint8_t, 8> MP4_MAGIC = {0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70};
inline const Type TYPE_MP4{"video/mp4", "mp4"};

// AVI video format
// Magic: 52 49 46 46 XX XX XX XX 41 56 49 20 (RIFF....AVI )
inline const std::array<uint8_t, 12> AVI_MAGIC = {0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x41, 0x56, 0x49, 0x20};
inline const Type TYPE_AVI{"video/x-msvideo", "avi"};

// MKV video format
// Magic: 1A 45 DF A3 (.E..)
inline const std::array<uint8_t, 4> MKV_MAGIC = {0x1A, 0x45, 0xDF, 0xA3};
inline const Type TYPE_MKV{"video/x-matroska", "mkv"};

// WebM video format
// Magic: 1A 45 DF A3 (same as MKV)
inline const std::array<uint8_t, 4> WEBM_MAGIC = {0x1A, 0x45, 0xDF, 0xA3};
inline const Type TYPE_WEBM{"video/webm", "webm"};

// MOV video format
// Magic: 00 00 00 XX 66 74 79 70 71 74 20 20 (....ftypqt  )
inline const std::array<uint8_t, 12> MOV_MAGIC = {0x00, 0x00, 0x00, 0x14, 0x66, 0x74, 0x79, 0x70, 0x71, 0x74, 0x20, 0x20};
inline const Type TYPE_MOV{"video/quicktime", "mov"};

// FLV video format
// Magic: 46 4C 56 01 (FLV.)
inline const std::array<uint8_t, 4> FLV_MAGIC = {0x46, 0x4C, 0x56, 0x01};
inline const Type TYPE_FLV{"video/x-flv", "flv"};

// WMV video format
// Magic: 30 26 B2 75 8E 66 CF 11 (same header as ASF)
inline const std::array<uint8_t, 8> WMV_MAGIC = {0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11};
inline const Type TYPE_WMV{"video/x-ms-wmv", "wmv"};

// MPEG video format
// Magic: 00 00 01 BA or 00 00 01 B3
inline const std::array<uint8_t, 4> MPEG_MAGIC = {0x00, 0x00, 0x01, 0xBA};
inline const std::array<uint8_t, 4> MPEG_MAGIC_ALT = {0x00, 0x00, 0x01, 0xB3};
inline const Type TYPE_MPEG{"video/mpeg", "mpg"};

// 3GP video format
// Magic: 00 00 00 XX 66 74 79 70 33 67 70 (....ftyp3gp)
inline const std::array<uint8_t, 11> THREEGP_MAGIC = {0x00, 0x00, 0x00, 0x14, 0x66, 0x74, 0x79, 0x70, 0x33, 0x67, 0x70};
inline const Type TYPE_3GP{"video/3gpp", "3gp"};

} // namespace video
} // namespace filetype

#endif // FILETYPE_TYPES_VIDEO_TYPES_HPP
