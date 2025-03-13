#ifndef FILETYPE_HPP
#define FILETYPE_HPP

/**
 * @file filetype.hpp
 * @brief Main header file for the cpp-filetype library
 * 
 * This library provides functionality to detect file types based on their magic numbers.
 * Supported file types include images, documents, archives, audio, and video formats.
 * 
 * @example
 * ```cpp
 * #include <filetype/filetype.hpp>
 * #include <fstream>
 * #include <vector>
 * 
 * int main() {
 *     // Read file bytes
 *     std::ifstream file("example.png", std::ios::binary);
 *     std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(file), {});
 *     
 *     // Detect file type
 *     const filetype::Type* type = filetype::match(buffer);
 *     if (type != nullptr) {
 *         std::cout << "MIME: " << type->mime << std::endl;
 *         std::cout << "Extension: " << type->extension << std::endl;
 *     } else {
 *         std::cout << "Unknown file type" << std::endl;
 *     }
 *     
 *     return 0;
 * }
 * ```
 * 
 * @version 0.1.0
 */

#include <array>
#include <vector>
#include <cstdint>
#include <string>
#include <string_view>

#include "types.hpp"

namespace filetype {

/**
 * @brief Validate if a buffer has sufficient data for type detection.
 * 
 * @param bytes Input buffer to validate.
 * @param min_size Minimum required size for the buffer (default: 8 bytes).
 * @return true if buffer is valid and has sufficient size.
 */
bool is_valid_buffer(const std::vector<uint8_t>& bytes, size_t min_size = 8);

/**
 * @brief Compare bytes with a magic number pattern.
 * 
 * @param bytes Buffer containing file data.
 * @param magic Pointer to magic number sequence.
 * @param magic_size Length of the magic number sequence.
 * @param offset Offset in bytes where to start matching (default: 0).
 * @return true if bytes match the magic number pattern.
 */
bool match_magic(const std::vector<uint8_t>& bytes, 
                   const uint8_t* magic, 
                   size_t magic_size,
                   size_t offset = 0);

/**
 * @brief Template version of match_magic for std::array magic numbers.
 * 
 * @tparam N Size of the magic number array.
 * @param bytes Buffer containing file data.
 * @param magic Array containing the magic number sequence.
 * @param offset Offset in bytes where to start matching (default: 0).
 * @return true if bytes match the magic number pattern.
 */
template <size_t N>
bool match_magic(const std::vector<uint8_t>& bytes,
                 const std::array<uint8_t, N>& magic,
                 size_t offset = 0) {
    return match_magic(bytes, magic.data(), N, offset);
}

/**
 * @brief Check if the file type matches a specific format.
 * 
 * @param bytes Buffer containing file data.
 * @param magic Magic number sequence to match.
 * @param magic_size Size of the magic number sequence.
 * @param offset Offset where the magic number should appear (default: 0).
 * @return true if the file matches the specified format.
 */
bool is_type(const std::vector<uint8_t>& bytes, 
             const uint8_t* magic, 
             size_t magic_size,
             size_t offset = 0);

/**
 * @brief Template version of is_type for std::array magic numbers.
 * 
 * @tparam N Size of the magic number array.
 * @param bytes Buffer containing file data.
 * @param magic Array containing the magic number sequence.
 * @param offset Offset where the magic number should appear (default: 0).
 * @return true if the file matches the specified format.
 */
template <size_t N>
bool is_type(const std::vector<uint8_t>& bytes,
             const std::array<uint8_t, N>& magic,
             size_t offset = 0) {
    return is_type(bytes, magic.data(), N, offset);
}

/**
 * @brief Detect file type from a byte buffer.
 * 
 * This function attempts to detect the file type by comparing the buffer's contents
 * with known magic numbers of various file formats.
 * 
 * @param bytes Buffer containing the file data to analyze.
 * @return Pointer to the detected file type, or nullptr if type could not be determined.
 */
const Type* match(const std::vector<uint8_t>& bytes);

/**
 * @brief Detect file type from a file path.
 * 
 * This function reads the beginning of the file and attempts to detect its type
 * by comparing with known magic numbers.
 * 
 * @param filepath Path to the file to analyze.
 * @param max_read_size Maximum number of bytes to read from the file (default: 8192).
 * @return Pointer to the detected file type, or nullptr if type could not be determined.
 */
const Type* match_file(std::string_view filepath, size_t max_read_size = 8192);

/**
 * @brief Check if file has a specific type.
 * 
 * @param bytes Buffer containing file data.
 * @param type Type to check against.
 * @return true if file matches the given type.
 */
bool is(const std::vector<uint8_t>& bytes, const Type& type);

/**
 * @brief Check if file is an image.
 * 
 * @param bytes Buffer containing file data.
 * @return true if file is an image.
 */
bool is_image(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file is a document.
 * 
 * @param bytes Buffer containing file data.
 * @return true if file is a document.
 */
bool is_document(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file is an archive.
 * 
 * @param bytes Buffer containing file data.
 * @return true if file is an archive.
 */
bool is_archive(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file is an audio file.
 * 
 * @param bytes Buffer containing file data.
 * @return true if file is an audio file.
 */
bool is_audio(const std::vector<uint8_t>& bytes);

/**
 * @brief Check if file is a video file.
 * 
 * @param bytes Buffer containing file data.
 * @return true if file is a video file.
 */
bool is_video(const std::vector<uint8_t>& bytes);

namespace matcher {

/**
 * @brief Match image file types.
 * @param bytes Buffer containing file data.
 * @return Pointer to the detected image type, or nullptr if not an image.
 */
const Type* match_image(const std::vector<uint8_t>& bytes);

/**
 * @brief Match document file types.
 * @param bytes Buffer containing file data.
 * @return Pointer to the detected document type, or nullptr if not a document.
 */
const Type* match_document(const std::vector<uint8_t>& bytes);

/**
 * @brief Match archive file types.
 * @param bytes Buffer containing file data.
 * @return Pointer to the detected archive type, or nullptr if not an archive.
 */
const Type* match_archive(const std::vector<uint8_t>& bytes);

/**
 * @brief Match audio file types.
 * @param bytes Buffer containing file data.
 * @return Pointer to the detected audio type, or nullptr if not an audio file.
 */
const Type* match_audio(const std::vector<uint8_t>& bytes);

/**
 * @brief Match video file types.
 * @param bytes Buffer containing file data.
 * @return Pointer to the detected video type, or nullptr if not a video file.
 */
const Type* match_video(const std::vector<uint8_t>& bytes);

} // namespace matcher

} // namespace filetype

#endif // FILETYPE_HPP
