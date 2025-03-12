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

## License

MIT License (c) 2025 Prince Roshan