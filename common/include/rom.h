#ifndef CHIPPY_ROM_H
#define CHIPPY_ROM_H

#include <stdint.h>

/* Roms are the actual programs that chip8 will run */
typedef struct {
    const uint8_t* memory;
    char* name;
} Rom;

/* Create a rom on the heap */
Rom* LoadRom(const char* filepath);

/* Destroy a heap allocated rom and the data allocated within it */
void DestroyRom(Rom** rom);

#endif