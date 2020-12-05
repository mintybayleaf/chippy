# Include CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

list(APPEND CHIPPY_COMMON_SOURCE src/loader.c)

target_sources(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CHIPPY_COMMON_SOURCE}"
)

target_sources(
    ${CHIPPY_DISASSEMBLER_TARGET}
    PRIVATE "${CHIPPY_COMMON_SOURCE}"
)

target_include_directories(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "include"
)

target_include_directories(
    ${CHIPPY_DISASSEMBLER_TARGET}
    PRIVATE "include"
)
