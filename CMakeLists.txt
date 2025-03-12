cmake_minimum_required(VERSION 3.14)
project(cpp-filetype VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download and configure Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

# Create the library target
add_library(filetype
    src/filetype.cpp
)

target_include_directories(filetype
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create test target
enable_testing()
add_executable(filetype_test
    test/filetype_test.cpp
)

target_link_libraries(filetype_test
    PRIVATE
        filetype
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(filetype_test)

