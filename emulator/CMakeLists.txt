# Include CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

list(APPEND CHIPPY_EMULATOR_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/chip8.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/rom.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/gui.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/error.c"
)

if (NOT USE_SYSTEM_SDL2)
    # SDL2 Specific
    target_include_directories(${CHIPPY_EMULATOR_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl2/include")
    target_link_libraries(${CHIPPY_EMULATOR_TARGET} PRIVATE SDL2main SDL2-static) 
else()
    target_include_directories(${CHIPPY_EMULATOR_TARGET} PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(${CHIPPY_EMULATOR_TARGET} PRIVATE ${SDL2_LIBRARIES}) 
endif()

target_include_directories(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_sources(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CHIPPY_EMULATOR_SOURCES}"
)

# Compiler Flags
if(MSVC)
    target_compile_options(
        ${CHIPPY_EMULATOR_TARGET}
        PRIVATE /W4 /WX
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(
        ${CHIPPY_EMULATOR_TARGET}
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

target_compile_definitions(${CHIPPY_EMULATOR_TARGET} PRIVATE $<$<CONFIG:RELEASE>:NDEBUG>)
set_target_properties(${CHIPPY_EMULATOR_TARGET} PROPERTIES C_STANDARD 11)
set_target_properties(${CHIPPY_EMULATOR_TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 

add_custom_target(run
    COMMAND ${CHIPPY_EMULATOR_TARGET}
    DEPENDS ${CHIPPY_EMULATOR_TARGET}
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)