#include "rom.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

rom *loadFromFile(const char *filename,size_t *size){
    
    FILE *f = fopen(filename,"r");
    if(f == NULL){
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    *size = ftell(f);

    fseek(f, 0, SEEK_SET);
    rom *rom_data = (rom *)malloc(*size);
    if (rom_data == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(f);
        return NULL;
    }
    fread(rom_data, *size, 1, f);
    fclose(f);
    return rom_data;
}