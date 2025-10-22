
set(CMAKE_DISABLE_FIND_PACKAGE_spdlog ON)
find_package(spdlog QUIET)

if(NOT spdlog_FOUND)
  include(FetchContent)

  set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "" FORCE)
  set(FMT_SYS OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.13.0
  )

  FetchContent_MakeAvailable(spdlog)

  # Disable warnings for all spdlog sources
  if(TARGET spdlog)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
      target_compile_options(spdlog PRIVATE -w)
    elseif(MSVC)
      target_compile_options(spdlog PRIVATE /w)
    endif()
  endif()
endif()
