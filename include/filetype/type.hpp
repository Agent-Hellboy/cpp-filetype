#ifndef FILETYPE_TYPE_HPP
#define FILETYPE_TYPE_HPP

#include <string>

namespace filetype {

/// Common Type struct used across all file formats.
struct Type {
    std::string mime;       ///< MIME type of the file.
    std::string extension;  ///< File extension without the dot.

    Type(const std::string& m, const std::string& ext) : mime(m), extension(ext) {}

    bool operator==(const Type& other) const {
        return mime == other.mime && extension == other.extension;
    }
};

}  // namespace filetype

#endif  // FILETYPE_TYPE_HPP
