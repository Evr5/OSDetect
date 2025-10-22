# C++ CMake Starter Template

> 🧰 This repository is a reusable C++ + CMake starter template.  
> Click on "**Use this template**" (top right of the page) to start your own project based on it.

This repository provides a clean and cross-platform C++ project template using **CMake** and **Makefile**. It is designed for modern C++ development with easy compilation on **Linux**, **Windows**, and **macOS**, and supports both **static** and **dynamic linking**.

## ✅ Features

- 🧱 Minimal and modular `CMakeLists.txt`
- 🔧 Customizable `Makefile` (Release / Debug / Clean)
- 📦 Static linking support via `BUILD_STATIC` option
- 🛠️ Support for `Debug` and `Release` builds
- 💡 Automatically generates `compile_commands.json` for LSPs
- 🪟🖥️ Compatible with Windows, macOS, and Linux
- 🧪 Ready for unit testing integration

---

## 📁 Project Structure

```sh
project-root/
├── CMakeLists.txt
├── Makefile
├── src/
│   └── main.cpp
```

---

## 🚀 Quick Start

### 🖥️ Linux / macOS

#### Release build

```sh
make
```

#### Debug build

```sh
make debug
```

#### Static builds

```sh
make static
```

#### Install binaries

```sh
sudo make install
```

It will install the binaries in `/usr/local/bin/`

#### Launch tests

```sh
make test
```

#### Clean builds

```sh
make clean
```

#### Run the program

```sh
./MyProject
```

#### Show available Makefile targets

You can run:

```sh
make help
```

to display all available build targets and customizable variables.

### 🪟 Windows (MinGW or WSL)

```sh
make
# or use CMake directly
cmake -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_STATIC=ON
cmake --build build
```

---

## ⚙️ CMake Options

| Option              | Default | Description                             |
|---------------------|---------|-----------------------------------------|
| `BUILD_STATIC`      | OFF     | Enables static linking of stdlib/gcc    |
| `CMAKE_BUILD_TYPE`  | Release | Enables optimization or debug symbols   |

---

## 🛠️ Output Directory

You can change the output directory of the final binary by modifying the following line in the `Makefile`:

```make
OUTPUT_DIR := .  # Output directory for binaries (can be changed as needed)
```

This lets you control whether the binary appears in the project root, a `bin/` folder, or elsewhere.

---

## 🧪 Testing (Optional)

The CMake config includes a placeholder for adding tests:

```cmake
enable_testing()
# add_subdirectory(test)
```

---

## 🧑‍💻 Use as a template

To adapt this template to your project:

1. **Change the project name**  
   Modify the following line in `CMakeLists.txt` :

   ```cmake
   project(MyProject VERSION 0.1.0 LANGUAGES CXX)
   ```

   Replace `MyProject` with your project name.

2. **Add your source files**  
   Place your `.cpp` files in `src/` and your headers in `include/`.
   CMakeLists automatically detects new files.

3. **Add dependencies**
    Use `find_package()` or `add_subdirectory()` in `CMakeLists.txt` to integrate external libraries.

4. **Disable Tests**
    Set `-DBUILD_TESTS=OFF` to CMake or modify the option in the file.

5. **Change the Output Folder**
    Modify the `OUTPUT_DIR` variable in the `Makefile`.

---

## 📚 Add external libraries with FetchContent (modular method)

To add an external dependency using `FetchContent`, you can:

1. Create a `.cmake` file for the library inside the `cmake` folder.
2. Use `include(...)` in your `CMakeLists.txt` to load it.
3. Link it to your targets.

### 🛠 Example: Adding `fmt`

#### 1. Create a new file at `cmake/fmt.cmake`

```cmake
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        11.2.0
)

FetchContent_MakeAvailable(fmt)
```

#### 2. Modify your `CMakeLists.txt`

At the top of your `CMakeLists.txt`, add:

```cmake
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(fmt)
```

Then link `fmt` to your target:

```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)
```

#### 3. Use the library in your code

In the `main.cpp`:

```cpp
#include <fmt/core.h>

int main() {
    fmt::print("Hello, formatted world!\n");
    return 0;
}
```

This method keeps your project modular and clean, especially when managing multiple dependencies.

---

## 🧰 Requirements

### 🖥️ Linux/macOS

Make sure you have the following installed:

```sh
sudo apt install build-essential cmake
```

Or on macOS (with Homebrew):

```sh
brew install cmake
```

### 🪟 Windows (with MinGW or VS)

Install:

- `CMake`

- A C++ compiler like:
  - **MinGW** (e.g. via MSYS2 or WinLibs)
  - **Visual Studio with Desktop C++ Tools**

Make sure `cmake`, `make` (or ninja) are installed and your compiler are in the PATH.

---

## 📄 License

This project is licensed under the [MIT License](./LICENSE) — feel free to use it as a boilerplate for your own C++ projects.

---

## ✨ Author

Made with ❤️ by [Evr5](https://github.com/Evr5)
Feel free to contribute, fork, or suggest improvements!
