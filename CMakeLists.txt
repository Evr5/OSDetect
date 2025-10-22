cmake_minimum_required(VERSION 3.15)

project(OSDetect VERSION 0.1.0 LANGUAGES CXX)

# Add custom CMake modules path (optional, juust need to include the name of the module)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Options
option(BUILD_STATIC "Link standard libs statically" OFF)

# Export compile_commands.json for LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# C++ standard (easily modifiable)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Static linking (fully static - cross-platform)
if(BUILD_STATIC)
    message(STATUS "Static linking enabled")

    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        # Link everything statically, including libc
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
        set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    endif()
endif()

# Compilation flags
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -pedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options(-g -fsanitize=address,undefined)
        add_link_options(-fsanitize=address,undefined)
    else()
        add_compile_options(-O3 -DNDEBUG)
    endif()
endif()

# Define the minimum Windows version for compatibility
if(WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0600)
endif()

# Source and include directories
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Main library
add_library(${PROJECT_NAME} STATIC ${SOURCES})

# External libraries target
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

# Installation
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Include public headers
target_include_directories(OSDetect PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Installation
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    EXPORT OSDetectTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Prevent exporting dependencies that are not installed
set_target_properties(${PROJECT_NAME} PROPERTIES
    EXPORT_EXCLUDE_FROM_ALL TRUE
)


# Export for find_package
install(EXPORT OSDetectTargets
    FILE OSDetectTargets.cmake
    NAMESPACE OSDetect::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/OSDetect
)

# Example executable (for testing the library)
add_executable(osdetect_example examples/main.cpp)
target_link_libraries(osdetect_example PRIVATE OSDetect)
target_include_directories(osdetect_example PRIVATE ${CMAKE_SOURCE_DIR}/include)
