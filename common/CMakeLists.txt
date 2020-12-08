# Include CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

list(APPEND CHIPPY_COMMON_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/rom.c" "${CMAKE_CURRENT_SOURCE_DIR}/src/instructions.c")

target_sources(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CHIPPY_COMMON_SOURCE}"
)

target_include_directories(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
