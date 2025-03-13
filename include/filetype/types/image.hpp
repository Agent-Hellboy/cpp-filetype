#ifndef FILETYPE_TYPES_IMAGE_HPP
#define FILETYPE_TYPES_IMAGE_HPP

#include <array>
#include <cstdint>
#include "filetype/type.hpp" 

namespace filetype {
namespace image {

using Type = ::filetype::Type; 

//------------------------------------------------------------------------------
// Image file type definitions
//------------------------------------------------------------------------------

/**
 * @brief PNG image format
 * Magic: 89 50 4E 47 0D 0A 1A 0A
 */
inline const std::array<uint8_t, 8> PNG_MAGIC = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
inline const Type TYPE_PNG{"image/png", "png"};

/**
 * @brief JPEG image format
 * Magic: FF D8 FF
 */
inline const std::array<uint8_t, 3> JPEG_MAGIC = {0xFF, 0xD8, 0xFF};
inline const Type TYPE_JPEG{"image/jpeg", "jpg"};

/**
 * @brief GIF image format
 * Magic: 47 49 46 38 (GIF8)
 */
inline const std::array<uint8_t, 6> GIF_MAGIC = {0x47, 0x49, 0x46, 0x38, 0x39, 0x61}; // Represents "GIF89a"
inline const Type TYPE_GIF{"image/gif", "gif"};

/**
 * @brief WebP image format
 * Magic: 52 49 46 46 ?? ?? ?? ?? 57 45 42 50 (RIFF....WEBP)
 */
inline const std::array<uint8_t, 12> WEBP_MAGIC = {0x52, 0x49, 0x46, 0x46, 0x00, 0x00, 0x00, 0x00, 0x57, 0x45, 0x42, 0x50};
inline const Type TYPE_WEBP{"image/webp", "webp"};

/**
 * @brief Canon Raw v2 image format
 * Magic: 49 49 2A 00 10 00 00 00
 */
inline const std::array<uint8_t, 8> CR2_MAGIC = {0x49, 0x49, 0x2A, 0x00, 0x10, 0x00, 0x00, 0x00};
inline const Type TYPE_CR2{"image/x-canon-cr2", "cr2"};

/**
 * @brief TIFF image format (little-endian)
 * Magic: 49 49 2A 00 (II*)
 */
inline const std::array<uint8_t, 4> TIFF_MAGIC_LE = {0x49, 0x49, 0x2A, 0x00};

/**
 * @brief TIFF image format (big-endian)
 * Magic: 4D 4D 00 2A (MM*. )
 */
inline const std::array<uint8_t, 4> TIFF_MAGIC_BE = {0x4D, 0x4D, 0x00, 0x2A};
inline const Type TYPE_TIFF{"image/tiff", "tif"};

/**
 * @brief BMP image format
 * Magic: 42 4D (BM)
 */
inline const std::array<uint8_t, 2> BMP_MAGIC = {0x42, 0x4D};
inline const Type TYPE_BMP{"image/bmp", "bmp"};

/**
 * @brief JPEG XR image format
 * Magic: 49 49 BC
 */
inline const std::array<uint8_t, 3> JXR_MAGIC = {0x49, 0x49, 0xBC};
inline const Type TYPE_JXR{"image/vnd.ms-photo", "jxr"};

/**
 * @brief Photoshop Document format
 * Magic: 38 42 50 53 (8BPS)
 */
inline const std::array<uint8_t, 4> PSD_MAGIC = {0x38, 0x42, 0x50, 0x53};
inline const Type TYPE_PSD{"image/vnd.adobe.photoshop", "psd"};

/**
 * @brief ICO image format
 * Magic: 00 00 01 00
 */
inline const std::array<uint8_t, 4> ICO_MAGIC = {0x00, 0x00, 0x01, 0x00};
inline const Type TYPE_ICO{"image/x-icon", "ico"};

/**
 * @brief HEIC image format (High Efficiency Image Format)
 * Magic: 00 00 00 ?? 66 74 79 70 68 65 69 63 (....ftyp heic)
 */
inline const std::array<uint8_t, 12> HEIC_MAGIC = {0x00, 0x00, 0x00, 0x18, 0x66, 0x74, 0x79, 0x70, 0x68, 0x65, 0x69, 0x63};
inline const Type TYPE_HEIC{"image/heic", "heic"};

} 
} 

#endif // FILETYPE_TYPES_IMAGE_HPP
