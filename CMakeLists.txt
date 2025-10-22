cmake_minimum_required(VERSION 3.15)

# === [EDIT HERE TO CHANGE PROJECT NAME] ===
project(MyProject VERSION 0.1.0 LANGUAGES CXX)

# Add custom CMake modules path (optional, juust need to include the name of the module)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(spdlog)

# Options
option(BUILD_STATIC "Link standard libs statically" OFF)
option(BUILD_TESTS "Build unit tests" ON)

# Export compile_commands.json for LSPs
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# User-defined test directory (can be overridden from CLI or Makefile)
set(TEST_DIR "${CMAKE_SOURCE_DIR}/tests" CACHE PATH "Path to test directory")

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

# Main executable
add_executable(${PROJECT_NAME} ${SOURCES})

# External libraries target
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

# Include directories 
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Installation
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Unit tests (preparation)
if(BUILD_TESTS)
    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS ${TEST_DIR}/*.cpp)

    if(TEST_SOURCES)
        add_executable(tests ${TEST_SOURCES})
        target_link_libraries(tests PRIVATE spdlog::spdlog_header_only)
        target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)

        # Set the binary in build/tests/
        set_target_properties(tests PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
        )

        add_test(NAME basic_test COMMAND ${CMAKE_BINARY_DIR}/tests/tests)
    else()
        message(WARNING "No test files found in ${TEST_DIR}")
    endif()
endif()
