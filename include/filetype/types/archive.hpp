#ifndef FILETYPE_TYPES_ARCHIVE_HPP
#define FILETYPE_TYPES_ARCHIVE_HPP

#include <array>
#include <cstdint>
#include "filetype/type.hpp"

namespace filetype {
namespace archive {

using Type = ::filetype::Type;

//------------------------------------------------------------------------------
// Archive file type definitions
//------------------------------------------------------------------------------

// ZIP archive format
// Magic: 50 4B 03 04 (PK..)
inline const std::array<uint8_t, 4> ZIP_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_ZIP{"application/zip", "zip"};

// RAR archive format
// Magic: 52 61 72 21 1A 07 00 (Rar!..)
inline const std::array<uint8_t, 7> RAR_MAGIC = {0x52, 0x61, 0x72, 0x21, 0x1A, 0x07, 0x00};
inline const Type TYPE_RAR{"application/x-rar-compressed", "rar"};

// TAR archive format
// Magic: 75 73 74 61 72 (ustar) at offset 257
inline const std::array<uint8_t, 5> TAR_MAGIC = {0x75, 0x73, 0x74, 0x61, 0x72};
inline const Type TYPE_TAR{"application/x-tar", "tar"};

// 7Z archive format
// Magic: 37 7A BC AF 27 1C (7z..')
inline const std::array<uint8_t, 6> SEVEN_Z_MAGIC = {0x37, 0x7A, 0xBC, 0xAF, 0x27, 0x1C};
inline const Type TYPE_7Z{"application/x-7z-compressed", "7z"};

// GZ archive format
// Magic: 1F 8B 08 (GZip)
inline const std::array<uint8_t, 3> GZ_MAGIC = {0x1F, 0x8B, 0x08};
inline const Type TYPE_GZ{"application/gzip", "gz"};
inline const Type TYPE_GZIP{"application/gzip", "gzip"};

// BZ2 archive format
// Magic: 42 5A 68 (BZh)
inline const std::array<uint8_t, 3> BZ2_MAGIC = {0x42, 0x5A, 0x68};
inline const Type TYPE_BZ2{"application/x-bzip2", "bz2"};
inline const Type TYPE_BZIP2{"application/x-bzip2", "bzip2"};

// XZ archive format
// Magic: FD 37 7A 58 5A 00
inline const std::array<uint8_t, 6> XZ_MAGIC = {0xFD, 0x37, 0x7A, 0x58, 0x5A, 0x00};
inline const Type TYPE_XZ{"application/x-xz", "xz"};

// Z archive format (compress)
// Magic: 1F 9D
inline const std::array<uint8_t, 2> Z_MAGIC = {0x1F, 0x9D};
inline const Type TYPE_Z{"application/x-compress", "Z"};

// LZ (LZIP) archive format
// Magic: 4C 5A 49 50 (LZIP)
inline const std::array<uint8_t, 4> LZ_MAGIC = {0x4C, 0x5A, 0x49, 0x50};
inline const Type TYPE_LZ{"application/x-lzip", "lz"};

}  // namespace archive
}  // namespace filetype

#endif  // FILETYPE_TYPES_ARCHIVE_HPP
