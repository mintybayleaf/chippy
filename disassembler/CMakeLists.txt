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

if (MSVC)
    target_compile_options(
        ${CHIPPY_DISASSEMBLER_TARGET}
        PRIVATE /W4 /WX
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(
        ${CHIPPY_DISASSEMBLER_TARGET}
        PRIVATE -Wall
        -Wextra
        -pedantic
        -Werror
        -Wswitch-default
        -Wswitch-enum
        -Wcast-align
        -Wpointer-arith
        -Wundef
        -Wnested-externs
        -Wcast-qual
        -Wshadow
        -Wunreachable-code
        -Wfloat-equal
        $<$<CONFIG:RELEASE>:-O2>
    )
endif()

target_compile_definitions(${CHIPPY_DISASSEMBLER_TARGET} PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>)
set_target_properties(${CHIPPY_DISASSEMBLER_TARGET} PROPERTIES C_STANDARD 11)
set_target_properties(${CHIPPY_DISASSEMBLER_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_custom_target(run-dis
    COMMAND ${CHIPPY_DISASSEMBLER_TARGET}
    DEPENDS ${CHIPPY_DISASSEMBLER_TARGET}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)