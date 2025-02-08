#include "core.h"
#include "rom.h"
#include "jmp.h"
#include <stdint.h>

void jmp(vmstat* vmstat){
    int32_t offset = vmstat->pc+1;
    vmstat->pc = OPCODE(offset);
}

void jz(vmstat* vmstat){
    if(vmstat->mem->reg.eax == 0)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jnz(vmstat* vmstat){
    if(vmstat->mem->reg.eax != 0)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void je(vmstat* vmstat){
    if(vmstat->eflags.equal)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jne(vmstat* vmstat){
    if(!vmstat->eflags.equal)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jg(vmstat* vmstat){
    if(vmstat->eflags.bigthen)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jge(vmstat* vmstat){
    if(vmstat->eflags.bigthen || vmstat->eflags.equal)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jl(vmstat* vmstat){
    if(vmstat->eflags.smallthan)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void jle(vmstat* vmstat){
    if(vmstat->eflags.smallthan || vmstat->eflags.equal)
        jmp(vmstat);
    else vmstat->pc += 2;
}

void cmp(vmstat* vmstat){
    int32_t eax = vmstat->mem->reg.eax;
    int32_t ebx = vmstat->mem->reg.ebx;

    vmstat->eflags.bigthen = eax > ebx;
    vmstat->eflags.smallthan = eax < ebx;
    vmstat->eflags.equal = eax == ebx;
    vmstat->pc += 1;
}