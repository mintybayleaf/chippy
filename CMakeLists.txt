# CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

# Important Vars
set(PROJECT_NAME "chippy")

project(
    ${PROJECT_NAME}
    VERSION 0.0.1
    LANGUAGES C
)

# Disable insource builds
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In source builds not allowed, set -B and -H")
endif()

# Options
option(BUILD_TESTS "Build Tests" OFF)
option(USE_SYSTEM_SDL2 "Use system SDL2 libs instead" OFF)
option(USE_SDL2_STATIC "Use SDL2 Static" OFF)

set(CHIPPY_EMULATOR_TARGET "chippy")


if (NOT USE_SYSTEM_SDL2)
    # SDL2 Stuff
    # I added this to the top level instead of emulator/CMakeLists.txt so the generated build
    # paths would be the same
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/sdl2")
else()
    find_package(SDL2 REQUIRED)
endif()


# Add the final targets
# TODO Add Debugger just for fun?
add_executable(${CHIPPY_EMULATOR_TARGET})

# Project Stuff
# Add subdirectories
add_subdirectory(emulator)

# Maybe add tests
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

