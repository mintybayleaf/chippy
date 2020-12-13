#include "rom.h"

#include <string.h>
#include <stdio.h> // FILE*
#include <stdlib.h> // Free

Rom* LoadRom(const char* filepath) {
    FILE* file = fopen(filepath, "a+b");

    if (!file) {
        return NULL;
    }

    size_t filesize = ftell(file);

    Rom* rom = (Rom*)malloc(sizeof(Rom));

    if (!rom) {
        return NULL;
    }

    // Read data into Rom
    rom->memory = (uint8_t*)malloc(filesize);
    
    // Read the file into rom
    fseek(file, 0, SEEK_SET);
    fread(rom->memory, sizeof(uint8_t), filesize, file);
    rom->rom_size = filesize;

    // Get file name
    #if defined(WIN32)
        char *last_slash = strrchr(filepath, '\\');
    #else
        char *last_slash = strrchr(filepath, '/');
    #endif

    const char* read_from = NULL;
    size_t read_size = 0;

    if (last_slash != NULL) {
        read_from = last_slash + 1;
        read_size = strlen(read_from);
    } else {
        read_from = filepath;
        read_size = strlen(filepath);
    }

    // Set name
    rom->name = malloc(read_size + 1);
    strncpy(rom->name, read_from, read_size);
    rom->name[read_size] = '\0';

    return rom;
}

void DestroyRom(Rom** rom) {
    if (*rom) {
        if ((*rom)->name) {
            free((*rom)->name);
            (*rom)->name = NULL;
        }

        if ((*rom)->memory) {
            free((*rom)->memory);
            (*rom)->memory = NULL;
        }

        (*rom)->rom_size = 0U;

        free(*rom);
        *rom = NULL;
    }
}