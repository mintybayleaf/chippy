# Include CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

list(APPEND CHIPPY_DISASSEMBLER_SOURCES src/main.c)

target_include_directories(
    ${CHIPPY_DISASSEMBLER_TARGET}
     PRIVATE "include"
)

target_sources(
    ${CHIPPY_DISASSEMBLER_TARGET}
    PRIVATE "${CHIPPY_DISASSEMBLER_SOURCES}"
)

if(MSVC)
    target_compile_options(
        ${CHIPPY_DISASSEMBLER_TARGET}
        PRIVATE /W4 /WX
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(
        ${CHIPPY_DISASSEMBLER_TARGET}
        PRIVATE -Wall -Wextra -pedantic -Werror
        $<$<CONFIG:RELEASE>:-O2>
    )
endif()

set_target_properties(${CHIPPY_DISASSEMBLER_TARGET} PROPERTIES C_STANDARD 11)