# Contributing to cpp-filetype

Thank you for your interest in contributing to cpp-filetype! This document provides guidelines and instructions for contributing to this file type detection library.

## Table of Contents

- [Development Setup](#development-setup)
- [Coding Standards](#coding-standards)
- [Pull Request Process](#pull-request-process)
- [Testing Requirements](#testing-requirements)
- [Adding New File Types](#adding-new-file-types)
- [Documentation Guidelines](#documentation-guidelines)
- [Release Process](#release-process)

## Development Setup

### Prerequisites

- C++17 compatible compiler
- CMake 3.14 or higher
- Git
- Google Test (for running tests)

### Getting Started

1. Fork the repository on GitHub
2. Clone your fork locally:
   ```bash
   git clone https://github.com/YOUR_USERNAME/cpp-filetype.git
   cd cpp-filetype
   ```

3. Set up the build environment:
   ```bash
   mkdir build && cd build
   cmake -DBUILD_TESTING=ON -DBUILD_EXAMPLES=ON ..
   cmake --build .
   ```

4. Run the tests to ensure everything is working:
   ```bash
   ctest --output-on-failure
   ```

5. Create a new branch for your feature or bug fix:
   ```bash
   git checkout -b feature/your-feature-name
   ```

### Project Structure

- `include/filetype/` - Public API headers
- `include/filetype/types/` - Type definitions for different file categories
- `src/` - Implementation files
- `test/` - Test files
- `examples/` - Example usage
- `cmake/` - CMake configuration files

## Coding Standards

### C++ Style Guide

We follow a consistent coding style throughout the project:

- **Indentation**: 4 spaces (no tabs)
- **Naming Conventions**:
  - Use `snake_case` for variable and function names
  - Use `PascalCase` for class, struct, and type names
  - Use `UPPER_CASE` for constants and macros
- **Braces**: Opening braces on the same line for functions and control structures
- **Line Length**: Aim for a maximum of 100 characters
- **Comments**: Use Doxygen-style comments for public API elements

### Code Formatting

Consider using clang-format to automatically format your code. A `.clang-format` file is provided in the repository root.

```bash
# Format a specific file
clang-format -i include/filetype/filetype.hpp

# Format all files
find include src test -name "*.hpp" -o -name "*.cpp" | xargs clang-format -i
```

### Best Practices

- Prefer modern C++ features and idioms
- Use `std::optional` for functions that may not return a value
- Use `const` and `constexpr` where appropriate
- Avoid raw pointers, prefer smart pointers or references
- Keep functions focused and concise
- Write self-documenting code with meaningful names

## Pull Request Process

### Before Submitting

1. Update or add tests for your changes
2. Ensure all tests pass: `ctest --output-on-failure`
3. Update documentation to reflect any changes
4. Make sure your code follows our coding standards
5. Rebase your branch to include the latest changes from main

### Submitting a Pull Request

1. Push your changes to your fork:
   ```bash
   git push origin feature/your-feature-name
   ```

2. Create a new Pull Request through the GitHub interface
3. Use a clear and descriptive title
4. Include the following information in the description:
   - Summary of the changes
   - Why the changes are needed
   - Any breaking changes
   - Related issues (use GitHub keywords like "Fixes #123")

### Review Process

1. Maintainers will review your PR
2. Address any requested changes or feedback
3. Once approved, a maintainer will merge your PR
4. Your contribution will be acknowledged in the project's changelog

## Testing Requirements

### Writing Tests

- All new code should have corresponding tests
- Use Google Test framework for C++ unit tests
- Aim for high test coverage (especially edge cases)
- Test both success and failure paths

### Test Categories

1. **Unit Tests**: Test individual functions and classes
2. **Integration Tests**: Test interaction between components
3. **Edge Cases**:
   - Empty inputs
   - Malformed files
   - Incorrect magic numbers
   - Very large files
   - Files with partial magic numbers

### Running Tests

```bash
# Build and run all tests
cd build
cmake --build .
ctest --output-on-failure

# Run specific tests
./test/filetype_test --gtest_filter=FileTypeTest.DetectsImageFormats

# Run tests with verbose output
ctest -V
```

## Adding New File Types

### Research

1. Find the file format specification
2. Identify the magic number sequence (usually the first bytes of the file)
3. Determine the correct MIME type
4. Verify the standard file extension

### Implementation Steps

1. Select the appropriate category file (image, document, archive, audio, or video)
2. Add the magic number definition:
   ```cpp
   /**
    * @brief Example format description
    * Magic: 01 02 03 04 (hex representation)
    */
   const std::array<uint8_t, 4> EXAMPLE_MAGIC = {0x01, 0x02, 0x03, 0x04};
   const Type TYPE_EXAMPLE{"application/example", "example"};
   ```

3. Update the matcher function in `src/filetype.cpp`:
   ```cpp
   std::optional<Type> match_category(const std::vector<uint8_t>& bytes) {
       // Existing code...
       
       if (match_magic(bytes, EXAMPLE_MAGIC)) {
           return TYPE_EXAMPLE;
       }
       
       // Existing code...
   }
   ```

4. Add tests in `test/filetype_test.cpp`:
   ```cpp
   TEST_F(FileTypeTest, DetectsExampleFormat) {
       std::vector<uint8_t> example_data{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
       auto result = filetype::match(example_data);
       ASSERT_TRUE(result.has_value());
       EXPECT_EQ(result->mime, "application/example");
       EXPECT_EQ(result->extension, "example");
   }
   ```

5. Update the README.md to include the new format

### Testing New Types

- Create test files or byte sequences for the new format
- Test with both valid and invalid files
- Test edge cases (small files, corrupted headers)

## Documentation Guidelines

### Code Documentation

- Use Doxygen-style comments for all public API elements
- Document parameters, return values, and exceptions
- Include usage examples for complex functions
- Use meaningful names that don't need excessive comments

### Example Documentation

```cpp
/**
 * @brief Detect file type from a byte buffer
 * 
 * This function attempts to detect the file type by comparing the buffer's contents
 * with known magic numbers of various file formats.
 * 
 * @param bytes Buffer containing the file data to analyze
 * @return The detected file type, or std::nullopt if type could not be determined
 * 
 * @code
 * // Example usage:
 * std::vector<uint8_t> buffer = read_file("example.png");
 * auto type = filetype::match(buffer);
 * if (type) {
 *     std::cout << "MIME: " << type->mime << std::endl;
 * }
 * @endcode
 */
std::optional<Type> match(const std::vector<uint8_t>& bytes);
```

### README and Markdown

- Keep the README.md updated with new features and types
- Use clear and concise language
- Include code examples

## Release Process

1. Update version number in CMakeLists.txt
2. Update the CHANGELOG.md file
3. Create a new git tag with the version number
4. Create a GitHub release with release notes
5. Update documentation as needed

## Questions or Need Help?

- Open an issue on GitHub for questions or problems
- Join discussions on existing issues
- Reach out to maintainers via email

Thank you for contributing to cpp-filetype!

