# Solo's AnyHandle Library

**Solo's AnyHandle** is a small C++ header-only library providing the `any_handle` class,
a safe single container for type-erased pointers.

## Features

See [the documentation page](docs/SoloAnyHandleIndex.md).

## Usage
In your target's `CMakeLists.txt` file:
```cmake
find_package(solo-any-handle REQUIRED)
target_link_libraries(my_target PRIVATE solo::any_handle)
```

## Requirements

- C++14 or later
- CMake ≥ 3.15
- Optional:
    - Boost ≥ 1.72 (for extended package)
    - Stdex ≥ 1.0 (for extended package)

## Dependencies
- Compiles with C++14 compilers and later versions.
- Depends on STL library.
- The extended package depends on
    - [**Boost**](https://www.boost.org/libraries/latest/grid/) libraries.
    - [**Stdex**](https://nicolaspichon-git.github.io/stdex/) library.
