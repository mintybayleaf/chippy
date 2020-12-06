#include "insructions.h"

#define OPNONE 0x0u

/* Instruction info table */
const Instruction* GetInstructionInfo(InstructionEnum inst) {
    static const InstructionInfo* instruction_info[] = {
        &(Intruction){.nicename="CLS", .realname="CLS", description="00E0: CLS - Clear the display", .value=CLS},
        &(Intruction){.nicename="RETURN", .realname="RET", description="00EE: RET - Return from a subroutine", .value=RET},
        &(Intruction){.nicename="JUMP", .realname="JP", description="1nnn: JP addr - Jump to nnn, set PC to nnn", .value=JUMP},
        &(Intruction){.nicename="CALL", .realname="CALL", description="2nnn: CALL addr - Call subroutine at nnn", .value=CALL},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION IMMEDIATE", .realname="SE", description="3xkk: SE Vx, byte - Skip next instruction if Vx = kk", .value=SKIPNEXT_IMM},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION NOT IMMEDIATE".realname="SNE", description="4xkk: SNE Vx, byte - Skip next instruction if Vx != kk", .value=SKIPNEXTN_IMM},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION REGISTER".realname="SE", description="5xy0: SE Vx, Vy - Skip next instruction if Vx = Vy", .value=SKIPNEXT_REG},
        &(Intruction){.nicename="LOAD IMMEDIATE", .realname="LD", description="6xkk: LD Vx, byte - Set Vx = kk", .value=LOAD_IMM},
        &(Intruction){.nicename="ADD IMMEDIATE", .realname="ADD", description="7xkk: ADD Vx, byte - Set Vx = Vx + kk", .value=ADD_IMM},
        &(Intruction){.nicename="LOAD REGISTER".realname="LD", description="8xy0: LD Vx, Vy - Set Vx = Vy", .value=LOAD_REG},
        &(Intruction){.nicename="OR REGISTER", .realname="OR", description="8xy1: OR Vx, Vy - Set Vx = Vx OR Vy", .value=OR_REG},
        &(Intruction){.nicename="AND REGISTER", .realname="AND", description="8xy2: AND Vx, Vy - Set Vx = Vx AND Vy", .value=AND_REG},
        &(Intruction){.nicename="XOR REGISTER", .realname="XOR", description="8xy3: XOR Vx, Vy - Set Vx = Vx XOR Vy", .value=XOR_REG},
        &(Intruction){.nicename="ADD REGISTER", .realname="ADD", description="8xy4: ADD Vx, Vy - Set Vx = Vx + Vy, set VF = carry", .value=ADD_REG},
        &(Intruction){.nicename="SUB REGISTER SET BORROW", .realname="SUB", description="8xy5: SUB Vx, Vy - Set Vx = Vx - Vy, set VF = NOT borrow", .value=SUB_REG},
        &(Intruction){.nicename="SHIFT RIGHT", .realname="SHR", description="8xy6: SHR Vx - Set Vx = Vx SHR 1", .value=SHR},
        &(Intruction){.nicename="SUBN REGISTER SET BORROW", .realname="SUBN", description="8xy7: SUBN Vx, Vy - Set Vx = Vy - Vx, set VF = NOT borrow", .value=SUBN_REG},
        &(Intruction){.nicename="SHIFT LEFT", .realname="SHL", description="8xyE: SHL Vx {, Vy} - Set Vx = Vx SHL 1", .value=SHL},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION NO REGISTER", .realname="SNE", description="9xy0: SNE Vx, Vy - Skip next instruction if Vx != Vy", .value=SKIPNEXTN_REG},
        &(Intruction){.nicename="LOAD INDEX IMMEDIATE", .realname="LD", description="Annn: LD I, addr - Set I = nnn", .value=LOAD_IDX_IMM},
        &(Intruction){.nicename="JUMP WITH OFFSET IMMEDIATE", .realname="JP", description="Bnnn: JP V0, addr - Jump to location nnn + V0", .value=JUMP_ADD},
        &(Intruction){.nicename="SET RANDOM BYTE TO REGISTER", .realname="RND", description="Cxkk: RND Vx, byte, Set Vx = random byte AND kk", .value=RANDOM},
        &(Intruction){.nicename="DRAW SPRITE TO DISPLAY", .realname="DRW", description="Dxyn: DRW Vx, Vy, nibble - Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision", .value=DRAW},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION IF KEY", .realname="SKP", description="Ex9E: SKP Vx - Skip next instruction if key with the value of Vx is pressed", .value=SKIPNEXT_KEY},
        &(Intruction){.nicename="SKIP NEXT INSTRUCTION IF NOT KEY", .realname="SKNP", description="ExA1: SKNP Vx - Skip next instruction if key with the value of Vx is not pressed", .value=SKIPNEXTN_KEY},
        &(Intruction){.nicename="LOAD DELAY TIME INTO REGISTER", .realname="LD", description="Fx07: LD Vx, DT - Set Vx = delay timer value", .value=LOAD_DTIMER},
        &(Intruction){.nicename="WAIT FOR KEY PRESS INTO REGISTER", .realname="LD", description="Fx0A: LD Vx, K - Wait for a key press, store the value of the key in Vx", .value=STORE_KEY},
        &(Intruction){.nicename="SET DTIMER WITH REGISTER VALUE", .realname="LD", description="Fx15: LD DT, Vx - Set delay timer = Vx", .value=SET_DTIMER},
        &(Intruction){.nicename="SET SOUND TIMER WITH REGISTER VALUE", .realname="LD", description="Fx18: LD ST, Vx - Set sound timer = Vx", .value=SET_STIMER},
        &(Intruction){.nicename="ADD TO INDEX IMMEDIATE", .realname="ADD", description="Fx1E: ADD I, Vx - Set I = I + Vx", .value=ADD_IDX_REG},
        &(Intruction){.nicename="LOAD SPRITE INTO INDEX", .realname="LD", description="Fx29: LD F, Vx - Set I = location of sprite for digit Vx", .value=LOAD_IDX_SPRITE},
        &(Intruction){.nicename="STORE BCD REP", .realname="LD", description="Fx33: LD B, Vx - Store BCD representation of Vx in memory locations I, I+1, and I+2", .value=LOAD_BCD},
        &(Intruction){.nicename="STORE ALL REGISTERS AT INDEX", .realname="LD", description="Fx55: LD [I], Vx - Store registers V0 through Vx in memory starting at location I", .value=STORE_IDX_ALL},
        &(Intruction){.nicename="READ ALL REGISTERS AT INDEX", .realname="LD", description="Fx65: LD Vx, [I] - Read registers V0 through Vx from memory starting at location I", .value=LOAD_IDX_ALL},
    };
    assert(inst >= 0 && inst < INSTR_SET_SIZE);
    return instruction_info[inst]
}

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
