cmake_minimum_required(VERSION 3.14)
project(cpp-filetype VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable installation for Google Test so it won't be installed along with your project.
set(INSTALL_GTEST OFF CACHE BOOL "Disable installation of Google Test" FORCE)

# Download and configure Google Test
include(FetchContent)
fetchcontent_declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
fetchcontent_makeavailable(googletest)

# Create the library target
add_library(filetype
    src/filetype.cpp
)

target_include_directories(filetype
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Optionally export target for build-tree usage
export(TARGETS filetype FILE filetypeTargets.cmake)

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

#############################
# Installation and Export   #
#############################

# Install the library target to lib (which becomes /usr/local/lib)
install(TARGETS filetype
    EXPORT filetypeTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)

# Install public headers to include (which becomes /usr/local/include)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
)

# Export the targets with a namespace (e.g., filetype::) to lib/cmake/filetype
install(EXPORT filetypeTargets
    FILE filetypeTargets.cmake
    NAMESPACE filetype::
    DESTINATION lib/cmake/filetype
)

# Include helpers to generate the config files
include(CMakePackageConfigHelpers)

# Configure the filetypeConfig.cmake file to be installed in lib/cmake/filetype
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/filetypeConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/filetypeConfig.cmake
    INSTALL_DESTINATION lib/cmake/filetype
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

# Write the version file for the package
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/filetypeConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Install the package configuration files in lib/cmake/filetype
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/filetypeConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/filetypeConfigVersion.cmake
    DESTINATION lib/cmake/filetype
)
