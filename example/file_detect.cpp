// Copyright 2025 Prince Roshan <princekrroshan01@gmail.com>

/**
 * @file file_detect.cpp
 * @brief Example program to detect file types using magic numbers
 *
 * This program takes a file path as a command-line argument,
 * reads the file, and detects its type using the filetype library.
 * It then prints the detected MIME type and extension.
 */

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "filetype/filetype.hpp"

/**
 * @brief Print usage information for the program
 * @param program_name The name of the executable
 */
void print_usage(const char* program_name) {
  std::cerr
      << "Usage: " << program_name << " <file_path>\n"
      << "Detects the file type of the given file based on its magic number.\n";
}

/**
 * @brief Read file contents into a byte buffer
 * @param filepath Path to the file to read
 * @return Vector containing the file's bytes
 * @throws std::runtime_error if the file cannot be opened
 */
std::vector<uint8_t> read_file(const std::string& filepath) {
  std::ifstream file(filepath, std::ios::binary);
  if (!file) {
    throw std::runtime_error("Could not open file: " + filepath);
  }

  // Read file into buffer
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
  // Check command line arguments
  if (argc != 2) {
    print_usage(argv[0]);
    return EXIT_FAILURE;
  }

  const std::string filepath = argv[1];

  try {
    // Read file content
    std::vector<uint8_t> buffer = read_file(filepath);

    // Detect file type
    auto type = filetype::match(buffer);

    if (type) {
      std::cout << "File: " << filepath << "\n"
                << "MIME type: " << type->mime << "\n"
                << "Extension: ." << type->extension << "\n";

      // Determine file category
      if (filetype::is_image(buffer)) {
        std::cout << "Category: Image\n";
      } else if (filetype::is_document(buffer)) {
        std::cout << "Category: Document\n";
      } else if (filetype::is_archive(buffer)) {
        std::cout << "Category: Archive\n";
      } else if (filetype::is_audio(buffer)) {
        std::cout << "Category: Audio\n";
      } else if (filetype::is_video(buffer)) {
        std::cout << "Category: Video\n";
      } else {
        std::cout << "Category: Other\n";
      }
    } else {
      std::cout << "Unknown file type for: " << filepath << "\n";
    }
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
