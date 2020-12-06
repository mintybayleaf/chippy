#ifndef CHIPPY_INSTRUCTIONS_H
#define CHIPPY_INSTRUCTIONS_H

#include <stdint.h>

typedef enum {
    CLS,                // 00E0: CLS - Clear the display
    RET,                // 00EE: RET - Return from a subroutine
    JUMP,               // 1nnn: JP addr - Jump to nnn, set PC to nnn
    CALL,               // 2nnn: CALL addr - Call subroutine at nnn
    SKIPNEXT_IMM,       // 3xkk: SE Vx, byte - Skip next instruction if Vx = kk
    SKIPNEXTN_IMM,      // 4xkk: SNE Vx, byte - Skip next instruction if Vx != kk
    SKIPNEXT_REG,       // 5xy0: SE Vx, Vy - Skip next instruction if Vx = Vy
    LOAD_IMM,           // 6xkk: LD Vx, byte - Set Vx = kk
    ADD_IMM,            // 7xkk: ADD Vx, byte - Set Vx = Vx + kk
    LOAD_REG,           // 8xy0: LD Vx, Vy - Set Vx = Vy
    OR_REG,             // 8xy1: OR Vx, Vy - Set Vx = Vx OR Vy
    AND_REG,            // 8xy2: AND Vx, Vy - Set Vx = Vx AND Vy
    XOR_REG,            // 8xy3: XOR Vx, Vy - Set Vx = Vx XOR Vy
    ADD_REG,            // 8xy4: ADD Vx, Vy - Set Vx = Vx + Vy, set VF = carry
    SUB_REG,            // 8xy5: SUB Vx, Vy - Set Vx = Vx - Vy, set VF = NOT borrow
    SHR,                // 8xy6: SHR Vx - Set Vx = Vx SHR 1
    SUBN_REG,           // 8xy7: SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow
    SHL,                // 8xyE: SHL Vx {, Vy} - Set Vx = Vx SHL 1
    SKIPNEXTN_REG,      // 9xy0: SNE Vx, Vy - Skip next instruction if Vx != Vy
    LOAD_IDX_IMM,       // Annn: LD I, addr - Set I = nnn
    JUMP_ADD,           // Bnnn: JP V0, addr - Jump to location nnn + V0
    RANDOM,             // Cxkk: RND Vx, byte, Set Vx = random byte AND kk
    DRAW,               // Dxyn: DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision
    SKIPNEXT_KEY,       // Ex9E: SKP Vx - Skip next instruction if key with the value of Vx is pressed
    SKIPNEXTN_KEY,      // ExA1: SKNP Vx - Skip next instruction if key with the value of Vx is not pressed
    LOAD_DTIMER,        // Fx07: LD Vx, DT - Set Vx = delay timer value
    STORE_KEY,          // Fx0A: LD Vx, K - Wait for a key press, store the value of the key in Vx
    SET_DTIMER,         // Fx15: LD DT, Vx - Set delay timer = Vx
    SET_STIMER,         // Fx18: LD ST, Vx - Set sound timer = Vx
    ADD_IDX_REG,        // Fx1E: ADD I, Vx - Set I = I + Vx
    LOAD_IDX_SPRITE,    // Fx29: LD F, Vx - Set I = location of sprite for digit Vx
    LOAD_BCD,           // Fx33: LD B, Vx - Store BCD representation of Vx in memory locations I, I+1, and I+2
    STORE_IDX_ALL,      // Fx55: LD [I], Vx - Store registers V0 through Vx in memory starting at location I
    LOAD_IDX_ALL,       // Fx65: LD Vx, [I] - Read registers V0 through Vx from memory starting at location I
    INSTR_SET_SIZE      // Total number of instructions in this enum
} InstructionEnum;

typedef struct {
    const char *nicename;
    const char *realname;
    const char *description;
    const InstructionEnum value;
} InstructionInfo;


#endif