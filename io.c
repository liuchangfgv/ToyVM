#include <stdio.h>
#include <stdint.h>

#include "rom.h"
#include "core.h"
#include "io.h"

void outstr(vmstat* vmstat){
    int32_t offset = OPCODE(vmstat->pc+1);
    char *str = (char *)((uint8_t *)vmstat->mem->mem + offset);
    printf("%s", str);
    vmstat->pc += 2;
}

void instr(vmstat* vmstat){
    int32_t offset = OPCODE(vmstat->pc+1);
    char *str = (char *)((uint8_t *)vmstat->mem->mem + offset);
    scanf("%s", str);
    vmstat->pc += 2;
}

void innum(vmstat* vmstat){
    int32_t offset = OPCODE(vmstat->pc+1);
    int32_t *num = (int32_t *)((uint8_t *)vmstat->mem->mem + offset);
    scanf("%d", num);
    vmstat->pc += 2;
}

void outnum(vmstat* vmstat){
    int32_t offset = OPCODE(vmstat->pc+1);
    int32_t *num = (int32_t *)((uint8_t *)vmstat->mem->mem + offset);
    printf("%d\n", *num);
    vmstat->pc += 2;
}