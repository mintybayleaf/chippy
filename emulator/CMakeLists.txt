# Include CMakeLists.txt

cmake_minimum_required(VERSION 3.13.4)

list(APPEND CHIPPY_EMULATOR_SOURCES src/main.c)

target_include_directories(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "include"
)

target_sources(
    ${CHIPPY_EMULATOR_TARGET}
    PRIVATE "${CHIPPY_EMULATOR_SOURCES}"
)

if(MSVC)
    target_compile_options(
        ${CHIPPY_EMULATOR_TARGET}
        PRIVATE /W4 /WX
        $<$<CONFIG:RELEASE>:/O2>
    )
else()
    target_compile_options(
        ${CHIPPY_EMULATOR_TARGET}
        PRIVATE -Wall -Wextra -pedantic -Werror
        $<$<CONFIG:RELEASE>:-O2>
    )
endif()

set_target_properties(${CHIPPY_EMULATOR_TARGET} PROPERTIES C_STANDARD 11)
target_include_directories(${CHIPPY_EMULATOR_TARGET} PRIVATE "${CMAKE_SOURCE_DIR}/external/sdl2/include")
target_link_libraries(${CHIPPY_EMULATOR_TARGET} SDL2main SDL2-static})    
