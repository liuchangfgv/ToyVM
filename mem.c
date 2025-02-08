#include <stdint.h>
#include "core.h"
#include "rom.h"
#include "mem.h"

void mov(vmstat* vmstat){
    int32_t src = vmstat->pc+1;
    int32_t dst = vmstat->pc+2;
    vmstat->mem->mem[OPCODE(dst)]  = vmstat->mem->mem[OPCODE(src)];
    vmstat->pc += 3;
}

void push(vmstat* vmstat){
    int32_t src = vmstat->pc+1;
    vmstat->mem->reg.esp -= 1;
    vmstat->mem->mem[vmstat->mem->reg.esp] = vmstat->mem->mem[OPCODE(src)];
    vmstat->pc += 2;
}

void pop(vmstat* vmstat){
    int32_t dst = vmstat->pc+1;
    vmstat->mem->mem[OPCODE(dst)] = vmstat->mem->mem[vmstat->mem->reg.esp];
    vmstat->mem->reg.esp += 1;
    vmstat->pc += 2;
}

void num(vmstat* vmstat){
    int32_t num = vmstat->pc+1;
    vmstat->mem->reg.eax = OPCODE(num);
    vmstat->pc += 2;
}

void mov8(vmstat* vmstat){
    int32_t src = vmstat->pc+1;
    int32_t dst = vmstat->pc+2;
    vmstat->mem->mem8[OPCODE(dst)] = vmstat->mem->mem8[OPCODE(src)];
    vmstat->pc += 3;
}