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

set(CHIPPY_EMULATOR_TARGET "chippy")


if (UNIX OR APPLE)
    # Just build from source, use static lib
    add_subdirectory("${CMAKE_SOURCE_DIR}/external/sdl2")
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

