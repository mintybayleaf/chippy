#ifndef CHIPPY_CHIP8_H
#define CHIPPY_CHIP8_H

#include <stdint.h>
#include "rom.h"

#define CHIP8_MEMORY_SIZE 4096U
#define CHIP8_VIDEO_SIZE (64U * 32U)

typedef struct chip8 {
    uint8_t registers[16];
    uint8_t memory[CHIP8_MEMORY_SIZE];
    uint16_t index;
    uint16_t pc;
    uint8_t sp;
    uint8_t delay_timer;
    uint8_t sound_timer;
    uint8_t keypad[16];
    uint32_t video[(64U * 32U)];
    uint16_t opcode;
} chip8;

// Init structure
void chip8_init(chip8* chip);

// Load rom into chip8 memory
void chip8_load_rom(chip8* chip, Rom* rom);

// Run the emulator in the fetch, decode, execute cycle
// Memory, Sound and other peripherals are all updated accordingly
void chip8_run(chip8* chip);

#endif