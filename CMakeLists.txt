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

set(CHIPPY_DISASSEMBLER_TARGET "chippy-dis")
set(CHIPPY_EMULATOR_TARGET "chippy")

# Add the final targets
# TODO Add Debugger just for fun?
add_executable(${CHIPPY_EMULATOR_TARGET})
add_executable(${CHIPPY_DISASSEMBLER_TARGET})

# Add subdirectories

# SDL2 Stuff
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_SOURCE_DIR}/external/sdl2")

# Project Stuff
add_subdirectory(emulator)
add_subdirectory(common)
add_subdirectory(disassembler)

# Maybe add tests
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()
