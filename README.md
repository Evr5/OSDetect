# 🧩 OSDetect

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-11%2B-blue.svg)](https://en.cppreference.com/w/cpp/11)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg)](#)

**OSDetect** is a lightweight, cross-platform C++ library that detects the operating system your program is running on — including detailed versions such as **Windows 10 / 11**, **macOS Sonama**, or **Linux distributions** like **Ubuntu**, **Arch**, or **NixOS**.

## 🚀 Features

✅ Detects the current operating system  
✅ Identifies detailed version or distribution  
✅ Works on **Windows**, **macOS**, and **Linux**  
✅ Simple, type-safe API using `enum class`  
✅ CMake-friendly and easy to integrate  

## 📦 Supported Platforms

|   OS Family   |  Details  |
|---------------|-----------|
|  **Windows**  | Windows 7, 8, 10, 11 (via native `RtlGetVersion`)
|   **macOS**   | Catalina → Tahoe (kernel-based detection)
|   **Linux**   | Ubuntu, Debian, Fedora, Arch, openSUSE, Manjaro, CentOS, Red Hat, Alpine, NixOS, etc.

## 🛠 Installation

### Option 1 — CMake FetchContent (recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  OSDetect
  GIT_REPOSITORY https://github.com/<your-username>/OSDetect.git
  GIT_TAG main
)
FetchContent_MakeAvailable(OSDetect)

target_link_libraries(your_target PRIVATE OSDetect)
```

### Option 2 — As a submodule

```bash
git submodule add https://github.com/Evr5/OSDetect.git external/OSDetect
```

Then in your CMakeLists.txt:

```cmake
add_subdirectory(external/OSDetect)
target_link_libraries(your_target PRIVATE OSDetect)
```

### Option 3 — System-wide installation

```bash
git clone https://github.com/Evr5/OSDetect.git
cd OSDetect
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target install
```

Then link it in your project:

```cmake
find_package(OSDetect REQUIRED)
target_link_libraries(your_target PRIVATE OSDetect::OSDetect)
```

## 💡 Usage Example

```cpp
#include "os_detect/OSDetect.h"
#include <iostream>

int main() {
    OSDetect::OS OS = OSDetect::getOS();
    std::cout << "Detected OS: " << OS << std::endl;

    switch (OS) {
        case OSDetect::OS::Windows:
            std::cout << "Windows Version: " << OSDetect::getWindowsVersion() << std::endl;
            break;
        case OSDetect::OS::MacOS:
            std::cout << "MacOS Version: " << OSDetect::getMacOSVersion() << std::endl;
            break;
        case OSDetect::OS::Linux:
            std::cout << "Linux Distro: " << OSDetect::getLinuxDistro() << std::endl;
            break;
        default:
            std::cout << "Unknown Version" << std::endl;
    }
    return 0;
}
```

**Example Output:**

```
Detected OS: Windows
Windows Version: Windows 11
```

```
Detected OS: Linux
Linux Distro: Ubuntu
```

```
Detected OS: macOS
macOS Version: macOS Sonoma (15)
```

## 📚 API Overview

| Function | Description |
|-----------|--------------|
| `OSDetect::getOS()` | Returns `OS::Windows`, `OS::MacOS`, `OS::Linux`, or `OS::Unknown`.|
| `OSDetect::getWindowsVersion()` | Returns a `WindowsVersion` enum (`Windows10`, `Windows11`, …). |
| `OSDetect::getMacOSVersion()` | Returns a `MacOSVersion` enum (`Ventura`, `Monterey`, …). |
| `OSDetect::getLinuxDistro()` | Returns a `LinuxDistro` enum (`Ubuntu`, `Arch`, `NixOS`, …). |
| `getDetailedOS<T>()` | Template wrapper returning the appropriate enum. |
| `operator<<` | Overloaded to print readable OS names to `std::ostream`. |

## 🧱 Build the Example

Linux - macOS:

```bash
make
./osdetect_example
```

Windows:

```bash
make
osdetect_example.exe
```

## 📂 Directory Structure

```
OSDetect/
├── include/
│   └── os_detect/
│       └── OSDetect.h
├── src/
│   └── OSDetect.cpp
├── examples/
│   └── main.cpp
├── CMakeLists.txt
├── Makefile 
└── README.md
```

## ⚙️ Requirements

- **C++11** or newer  
- **CMake 3.15+**  
- Works with **MSVC**, **GCC** and **Clang** 
- Cross-platform: Windows / Linux / macOS  

## 🧰 Contributing

Contributions and pull requests are welcome!  
If your OS or Linux distribution isn’t detected correctly, open an issue or submit a PR with a sample of your `/etc/os-release`.

## 📜 License

This project is licensed under the [**MIT License**](./LICENSE) — free for commercial and personal use.
