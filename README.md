# OSDetect

Small C++ utility for detecting the operating system.

## Installation via CMake FetchContent

```cmake
include(FetchContent)
FetchContent_Declare(
OSDetect
GIT_REPOSITORY https://github.com/Evr5/OSDetect.git
GIT_TAG main
)
FetchContent_MakeAvailable(OSDetect)

target_link_libraries(myapp PRIVATE OSDetect::OSDetect)
