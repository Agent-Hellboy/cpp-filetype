# cpp-filetype

A C++ library for detecting file types based on their magic bytes.

## Installation

### From Source

1. Clone the repository:
```bash
$ git clone https://github.com/agent-hellboy/cpp-filetype.git
```
2. Build and install:
```bash
$ rm -rf build
$ cd build
$ cmake -DBUILD_TESTS=ON ..
$ cmake --build .
$ ctest --output-on-failure
```
To install, run:
```bash
$ sudo cmake --build . --target install
```

installation will do below:
- install library to /usr/local/lib
- install headers to /usr/local/include
- install cmake configuration to /usr/local/lib/cmake/filetype

```bash
sudo cmake --build . --target install
[ 16%] Built target filetype
[ 33%] Built target gtest
[ 50%] Built target gtest_main
[ 66%] Built target filetype_test
[ 83%] Built target gmock
[100%] Built target gmock_main
Install the project...
-- Install configuration: ""
-- Installing: /usr/local/lib/libfiletype.a
-- Up-to-date: /usr/local/include
-- Up-to-date: /usr/local/include/filetype
-- Up-to-date: /usr/local/include/filetype/types
-- Up-to-date: /usr/local/include/filetype/types/document.hpp
-- Up-to-date: /usr/local/include/filetype/types/archive.hpp
-- Up-to-date: /usr/local/include/filetype/types/audio.hpp
-- Up-to-date: /usr/local/include/filetype/types/video.hpp
-- Up-to-date: /usr/local/include/filetype/types/image.hpp
-- Up-to-date: /usr/local/include/filetype/type.hpp
-- Up-to-date: /usr/local/include/filetype/types.hpp
-- Up-to-date: /usr/local/include/filetype/filetype.hpp
-- Installing: /usr/local/lib/cmake/filetype/filetypeTargets.cmake
-- Installing: /usr/local/lib/cmake/filetype/filetypeTargets-noconfig.cmake
-- Installing: /usr/local/lib/cmake/filetype/filetypeConfig.cmake
-- Installing: /usr/local/lib/cmake/filetype/filetypeConfigVersion.cmake
```

## Usage

```cpp
#include "filetype/filetype.hpp"

int main() {
    std::vector<uint8_t> data = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    const ::filetype::Type* type = ::filetype::match(data);
    if (type) {
        std::cout << "Detected: " << type->mime << " (" << type->extension << ")\n";
    } else {
        std::cout << "Unknown file type\n";
    }
    return 0;
}
```

Building example inside the repository:

```bash
g++ -std=c++17 -I../include ../src/filetype.cpp ../example/file_detect.cpp -o file_detect
```


## License

MIT License (c) 2025 Prince Roshan