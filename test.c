#include <stdio.h>
#include <stdlib.h>

int main() {
    const char* filepath = "roms/Tron.ch8";
    FILE* file = fopen(filepath, "r+b");
    if (!file) exit(1);
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    printf("Size: %ul", size);
}
