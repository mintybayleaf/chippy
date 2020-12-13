#include "chip8.h"
#include "error.h"

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

static const uint16_t START_ADDRESS = 0x200U;
static const unsigned int FONTSET_START_ADDRESS = 0x50;

enum { FONTSET_SIZE = 80 };
static uint8_t fontset[FONTSET_SIZE] =
{
	0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
	0x20, 0x60, 0x20, 0x20, 0x70, // 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
	0x90, 0x90, 0xF0, 0x10, 0x10, // 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
	0xF0, 0x10, 0x20, 0x40, 0x40, // 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
	0xF0, 0x90, 0xF0, 0x90, 0x90, // A
	0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
	0xF0, 0x80, 0x80, 0x80, 0xF0, // C
	0xE0, 0x90, 0x90, 0x90, 0xE0, // D
	0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
	0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

static uint8_t RandomByte() {
    return rand() % UINT8_MAX;
}


void Chip8Init(Chip8* chip) {
    memset(chip, 0, sizeof(Chip8));
    chip->pc = START_ADDRESS;

    // Load fonts into memory
    for (size_t i = 0; i < FONTSET_SIZE; i++) {
        chip->memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }
    
    // Seed random nums
    srand(time(NULL));
}

void Chip8LoadRom(Chip8* chip, Rom* rom) {
    if (rom->rom_size > (CHIP8_MEMORY_SIZE - START_ADDRESS)) {
        error("[ERRPR] ROM is too big %u", rom->rom_size);
    }
    memcpy(&chip->memory[START_ADDRESS], rom->memory, rom->rom_size);
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

#define INSTRUCTION(instruction) static void OP_##instruction (Chip8* chip)

// Clear the display (CLS)
static void OP_00E0(Chip8* chip) {
    // Its an array so size of is total bytes
    memset(chip->video, 0, sizeof(chip->video));
}

// Return on stack
static void OP_00EE(Chip8* chip) {
    chip->sp -= 1;
    chip->pc = chip->stack[chip->sp];
}

// Jp to location nnn
static void OP_1NNN(Chip8* chip, uint16_t opcode) {
    uint16_t address = opcode & 0x0FFFu;
    chip->pc = address;
}

// Call subroutine at nnn
static void OP_2NNN(Chip8* chip, uint16_t opcode) {
    uint16_t address = opcode & 0x0FFFu;
    chip->stack[chip->sp] = chip->pc;
    chip->sp += 1;
    chip->pc = address;
}

// Skip next instruction if Vx=kk
static void OP_3XKK(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    // Skip the pc ahead
    if (chip->registers[vx] == byte) {
        chip->pc += 2;
    }
}

// Skip next instruction if Vx!=Vk
static void OP_4XKK(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = opcode & 0x00FFu;

    if (chip->registers[vx] != byte) {
        chip->pc += 2;
    }
}

// Skip next if vx = vy
static void OP_5XY0(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t vy = (opcode & 0x00F0u) >> 4u;

    if (chip->registers[vx] == chip->registers[vy]) {
        chip->pc += 2;
    }
}

//Set vx = kk
static void OP_6XKK(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = (opcode & 0x00FFu);

    chip->registers[vx] = byte;
}

// Set vx = vx + kk
static void OP_7XKK(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = (opcode & 0x00FFu);

    chip->registers[vx] += byte;
}

// Set vx = vy
static void OP_8XY0(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    chip->registers[vx] = chip->registers[vy];
}

// Set vx = vx or vy
static void OP_8XY1(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    chip->registers[vx] |= chip->registers[vy];
}

// Set vx = vx and vy
static void OP_8XY2(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    chip->registers[vx] &= chip->registers[vy];
}

// Set vx = vx xor vy
static void OP_8XY3(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    chip->registers[vx] ^= chip->registers[vy];
}

// Set Vx = Vx + Vy, set VF = carry
static void OP_8XY4(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;
    uint16_t sum = chip->registers[vx] + chip->registers[vy];

    // Set VF
    if (sum > UINT8_MAX) {
        chip->registers[0xF] = 1;
    } else {
        chip->registers[0xF] = 0;
    }

    chip->registers[vx] = sum & 0xFFu;
}

// Set Vx = Vx - Vy, set VF = NOT borrow
static void OP_8XY5(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    // Set VF to not borrow
    if (chip->registers[vx] > chip->registers[vy]) {
        chip->registers[0xF] = 1;
    } else {
        chip->registers[0xF] = 0;
    }

    chip->registers[vx] -= chip->registers[vy];
}

// Set vx = vx shr 1
static void OP_8XY6(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;

    chip->registers[vx] >>= 1;
}

// Set Vx = Vy - Vx, set VF = NOT borrow
static void OP_8XY7(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    // Set VF to not borrow
    if (chip->registers[vy] > chip->registers[vx]) {
        chip->registers[0xF] = 1;
    } else {
        chip->registers[0xF] = 0;
    }

    chip->registers[vx] = chip->registers[vy] = chip->registers[vx];
}

// Set vx = vx shl 1
static void OP_8XYE(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;

    // Save MSB in 0xF
    chip->registers[0xF] = (chip->registers[vx] & 0x80u) >> 7u;
    chip->registers[vx] <<= 1;
}

// Skip next instruction if Vx != Vy
static void OP_9XY0(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;

    if (chip->registers[vx] != chip->registers[vy]) {
        chip->pc += 2;
    }
}

// Annn - LD I, addr
static void OP_ANNN(Chip8* chip, uint16_t opcode) {
    uint16_t address = opcode & 0x0FFFu;
    chip->index = address;
}

// Jump to location nnn + V0
static void OP_BNNN(Chip8* chip, uint16_t opcode) {
    uint16_t address = opcode & 0x0FFFu;
    chip->pc = chip->registers[0x0] + address;
}

// Set Vx = random byte AND kk
static void OP_CXKK(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t byte = (opcode & 0x00FFu);
    chip->registers[vx] = RandomByte() & byte;
}

// Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
static void OP_DXYN(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
	uint8_t vy = (opcode & 0x00F0u) >> 4u;
	uint8_t height = opcode & 0x000Fu;

    uint8_t xpos = chip->registers[vx] % CHIP8_VIDEO_WIDTH;
    uint8_t ypos = chip->registers[vy] % CHIP8_VIDEO_HEIGHT;

    chip->registers[0xF] = 0;

    for (size_t row = 0; row < height; ++row) {
        uint8_t sbyte = chip->memory[chip->index + row];
        for (size_t col = 0; col < 8; ++col) {
            uint8_t spixel = sbyte & (0x80u >> col);
            uint32_t* screenpixel = &chip->video[(ypos + row) * CHIP8_VIDEO_WIDTH + (xpos + col)];

            // When we want a sprite pixel we need to check if the screen already is on and if it is,
            // xor it and since we are using uint32_t for the display 0x00000000 is off, 0xFFFFFFFF is on
            // Sprite pixel is on
			if (spixel)
			{
				// Screen pixel also on - collision
				if (*screenpixel == 0xFFFFFFFF)
				{
					chip->registers[0xF] = 1;
				}

				// Effectively XOR with the sprite pixel
				*screenpixel ^= 0xFFFFFFFF;
			}
        }
    }
}

// Skip next instruction if key with the value of Vx is pressed
static void OP_EX9E(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = chip->registers[vx];

    if (chip->keypad[key]) {
        chip->pc += 2;
    }
}

// Skip next instruction if key with the value of Vx is not pressed
static void OP_EXA1(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t key = chip->registers[vx];

    if (!chip->keypad[key]) {
        chip->pc += 2;
    }
}

// Set Vx = delay timer value
static void OP_FX07(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    chip->registers[vx] = chip->delay_timer;
}

// Wait for a key press, store the value of the key in Vx
static void OP_FX0A(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;

    if (chip->keypad[0])
	{
		chip->registers[vx] = 0;
	}
	else if (chip->keypad[1])
	{
		chip->registers[vx] = 1;
	}
	else if (chip->keypad[2])
	{
		chip->registers[vx] = 2;
	}
	else if (chip->keypad[3])
	{
		chip->registers[vx] = 3;
	}
	else if (chip->keypad[4])
	{
		chip->registers[vx] = 4;
	}
	else if (chip->keypad[5])
	{
		chip->registers[vx] = 5;
	}
	else if (chip->keypad[6])
	{
		chip->registers[vx]= 6;
	}
	else if (chip->keypad[7])
	{
		chip->registers[vx] = 7;
	}
	else if (chip->keypad[8])
	{
		chip->registers[vx] = 8;
	}
	else if (chip->keypad[9])
	{
		chip->registers[vx] = 9;
	}
	else if (chip->keypad[10])
	{
		chip->registers[vx] = 10;
	}
	else if (chip->keypad[11])
	{
		chip->registers[vx] = 11;
	}
	else if (chip->keypad[12])
	{
		chip->registers[vx] = 12;
	}
	else if (chip->keypad[13])
	{
		chip->registers[vx] = 13;
	}
	else if (chip->keypad[14])
	{
		chip->registers[vx] = 14;
	}
	else if (chip->keypad[15])
	{
		chip->registers[vx] = 15;
	}
	else
	{
		chip->pc -= 2;
	}
}

// Set delay timer = Vx
static void OP_FX15(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    chip->delay_timer = chip->registers[vx];
}

// Set sound timer = Vx
static void OP_FX18(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    chip->sound_timer = chip->registers[vx];
}

// Set I = I + Vx
static void OP_FX1E(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    chip->index = chip->registers[vx];
}

// Set I = location of sprite for digit Vx
static void OP_FX29(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t digit = chip->registers[vx];
    chip->index = FONTSET_START_ADDRESS + (5 * digit);
}

// Store BCD representation of Vx in memory locations I, I+1, and I+2
static void OP_FX33(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    uint8_t value = chip->registers[vx];
    chip->memory[chip->index + 2] = value % 10;
    value /= 10;
    chip->memory[chip->index + 1] = value % 10;
    value /= 10;
    chip->memory[chip->index] = value % 10;
}

// Store registers V0 through Vx in memory starting at location I
static void OP_FX55(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    for(uint8_t i = 0; i < vx; ++i) {
        chip->memory[chip->index + i] = chip->registers[i];
    }
}

// Read registers V0 through Vx from memory starting at location I
static void OP_FX65(Chip8* chip, uint16_t opcode) {
    uint8_t vx = (opcode & 0x0F00u) >> 8u;
    for(uint8_t i = 0; i < vx; ++i) {
        chip->registers[i] = chip->memory[chip->index + i];
    }
}


void Chip8Cycle(Chip8* chip) {
    // Since im a lazy bitch and dont want to make a pointer table a case switch works hehe
    
    // Should be ROM start
    // Because endian problems ):
    uint16_t opcode = (chip->memory[chip->pc] << 8u) | chip->memory[chip->pc + 1];
    uint16_t expression = (opcode & 0xF000u) >> 12u;

    // Inc PC before executing
    chip->pc += 2;

    switch(expression) {
        case 0x0:
            switch(expression & 0x000Fu) {
                 case 0x0:
                    OP_00E0(chip);
                    break;
                case 0xE:
                    OP_00EE(chip);
                    break;
                default:
                    error("Invalid Opcode: %u", opcode);
                    break;
            }
            break;
        case 0x1:
            OP_1NNN(chip, opcode);
            break;
        case 0x2:
            OP_2NNN(chip, opcode);
            break;
        case 0x3:
            OP_3XKK(chip, opcode);
            break;
        case 0x4:
            OP_4XKK(chip, opcode);
            break;
        case 0x5:
            OP_5XY0(chip, opcode);
            break;
        case 0x6:
            OP_6XKK(chip, opcode);
            break;
        case 0x7:
            OP_7XKK(chip, opcode);
            break;
        case 0x8:
            switch(expression & 0x000Fu) {
                 case 0x0:
                    OP_8XY0(chip, opcode);
                    break;
                case 0x1:
                    OP_8XY1(chip, opcode);
                    break;
                case 0x2:
                    OP_8XY2(chip, opcode);
                    break;
                case 0x3:
                    OP_8XY3(chip, opcode);
                    break;
                case 0x4:
                    OP_8XY4(chip, opcode);
                    break;
                case 0x5:
                    OP_8XY5(chip, opcode);
                    break;
                case 0x6:
                    OP_8XY6(chip, opcode);
                    break;
                case 0x7:
                    OP_8XY7(chip, opcode);
                    break;
                 case 0xE:
                    OP_8XYE(chip, opcode);
                    break;
                default:
                    error("Invalid Opcode: %u", opcode);
                    break;
            }
           break;
        case 0x9:
            OP_9XY0(chip, opcode);
            break;
        case 0xA:
            OP_ANNN(chip, opcode);
            break;
        case 0xB:
            OP_BNNN(chip, opcode);
            break;
        case 0xC:
            OP_CXKK(chip, opcode);
            break;
        case 0xD:
            OP_DXYN(chip, opcode);
            break;
        case 0xE:
            switch(expression & 0x000Fu) {
                 case 0x1:
                    OP_EXA1(chip, opcode);
                    break;
                case 0xE:
                    OP_EX9E(chip, opcode);
                    break;
                default:
                    error("Invalid Opcode: %u", opcode);
                    break;
            }
            break;
        case 0xF:
            switch(expression & 0x00FFu) {
                 case 0x07:
                    OP_FX07(chip, opcode);
                    break;
                case 0x0A:
                    OP_FX0A(chip, opcode);
                    break;
                case 0x15:
                    OP_FX15(chip, opcode);
                    break;
                case 0x18:
                    OP_FX18(chip, opcode);
                    break;
                case 0x1E:
                    OP_FX1E(chip, opcode);
                    break;
                case 0x29:
                    OP_FX29(chip, opcode);
                    break;
                case 0x33:
                    OP_FX33(chip, opcode);
                    break;
                case 0x55:
                    OP_FX55(chip, opcode);
                    break;
                 case 0x65:
                    OP_FX65(chip, opcode);
                    break;
                default:
                    error("Invalid Opcode: %u", opcode);
                    break;
            }
           break;
            break;
        default:
            error("Invalid Opcode: %u", opcode);
            break;
    }

    // Decrement delay timer if its on
    if (chip->delay_timer > 0) {
        chip->delay_timer -= 1;
    }

    // Decrement sound timer if its on
    if (chip->sound_timer > 0) {
        chip->sound_timer -= 1;
    }
}






