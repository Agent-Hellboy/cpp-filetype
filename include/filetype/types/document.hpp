// Copyright 2025 Prince Roshan <princekrroshan01@gmail.com>

#ifndef INCLUDE_FILETYPE_TYPES_DOCUMENT_HPP_
#define INCLUDE_FILETYPE_TYPES_DOCUMENT_HPP_

#include <array>
#include <cstdint>

#include "filetype/type.hpp"

namespace filetype {
namespace document {

using Type = ::filetype::Type;

//------------------------------------------------------------------------------
// Document file type definitions
//------------------------------------------------------------------------------

// PDF document format
// Magic: 25 50 44 46 ("%PDF")
inline const std::array<uint8_t, 4> PDF_MAGIC = {0x25, 0x50, 0x44, 0x46};
inline const Type TYPE_PDF{"application/pdf", "pdf"};

// Microsoft DOC document format
// Magic: D0 CF 11 E0 A1 B1 1A E1 (Office Binary Document)
inline const std::array<uint8_t, 8> DOC_MAGIC = {0xD0, 0xCF, 0x11, 0xE0,
                                                 0xA1, 0xB1, 0x1A, 0xE1};
inline const Type TYPE_DOC{"application/msword", "doc"};

// Microsoft DOCX document format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> DOCX_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_DOCX{
    "application/vnd.openxmlformats-officedocument.wordprocessingml.document",
    "docx"};

// Microsoft XLS spreadsheet format
// Magic: D0 CF 11 E0 A1 B1 1A E1 (same as DOC)
inline const std::array<uint8_t, 8> XLS_MAGIC = {0xD0, 0xCF, 0x11, 0xE0,
                                                 0xA1, 0xB1, 0x1A, 0xE1};
inline const Type TYPE_XLS{"application/vnd.ms-excel", "xls"};

// Microsoft XLSX spreadsheet format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> XLSX_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_XLSX{
    "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet",
    "xlsx"};

// Microsoft PowerPoint presentation format
// Magic: D0 CF 11 E0 A1 B1 1A E1 (same as DOC)
inline const std::array<uint8_t, 8> PPT_MAGIC = {0xD0, 0xCF, 0x11, 0xE0,
                                                 0xA1, 0xB1, 0x1A, 0xE1};
inline const Type TYPE_PPT{"application/vnd.ms-powerpoint", "ppt"};

// Microsoft PowerPoint PPTX presentation format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> PPTX_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_PPTX{
    "application/vnd.openxmlformats-officedocument.presentationml.presentation",
    "pptx"};

// OpenDocument Text format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> ODT_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_ODT{"application/vnd.oasis.opendocument.text", "odt"};

// OpenDocument Spreadsheet format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> ODS_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_ODS{"application/vnd.oasis.opendocument.spreadsheet",
                           "ods"};

// OpenDocument Presentation format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> ODP_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_ODP{"application/vnd.oasis.opendocument.presentation",
                           "odp"};

// Rich Text Format
// Magic: 7B 5C 72 74 66 ("{\\rtf")
inline const std::array<uint8_t, 5> RTF_MAGIC = {0x7B, 0x5C, 0x72, 0x74, 0x66};
inline const Type TYPE_RTF{"application/rtf", "rtf"};

// EPUB document format
// Magic: 50 4B 03 04 (PK..)
// Note: This is a ZIP file signature; additional verification is needed.
inline const std::array<uint8_t, 4> EPUB_MAGIC = {0x50, 0x4B, 0x03, 0x04};
inline const Type TYPE_EPUB{"application/epub+zip", "epub"};

}  // namespace document
}  // namespace filetype

#endif  // INCLUDE_FILETYPE_TYPES_DOCUMENT_HPP_
