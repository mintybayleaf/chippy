#include "chip8.h"
#include "error.h"

#include <threads.h>
#include <string.h>

static const uint16_t START_ADDRESS = 0x200U;

void chip8_init(chip8* chip) {
    memset(chip, 0, sizeof(chip8));
    chip->pc = START_ADDRESS;
}

void chip8_load_rom(chip8* chip, Rom* rom) {
    if (rom->rom_size > (CHIP8_MEMORY_SIZE - START_ADDRESS)) {
        error("ROM size is too big to load into emulator... Aborting...");
    }
    memcpy(&chip->memory[START_ADDRESS], rom->memory, rom->rom_size);
}

void chip8_run(chip8* chip) {
    // Do stuff
    (void*)chip;
}

// Static opcode handlers below

/*
    The entire opcode is unique:
        $1nnn
        $2nnn
        $3xkk
        $4xkk
        $5xy0
        $6xkk
        $7xkk
        $9xy0
        $Annn
        $Bnnn
        $Cxkk
        $Dxyn
    The first digit repeats but the last digit is unique:
        $8xy0
        $8xy1
        $8xy2
        $8xy3
        $8xy4
        $8xy5
        $8xy6
        $8xy7
        $8xyE
    The first three digits are $00E but the fourth digit is unique:
        $00E0
        $00EE
    The first digit repeats but the last two digits are unique:
        $ExA1
        $Ex9E
        $Fx07
        $Fx0A
        $Fx15
        $Fx18
        $Fx1E
        $Fx29
        $Fx33
        $Fx55
        $Fx65
*/