#include "core.h"
#include "rom.h"
#include "alu.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void addOp(vmstat* vmstat){
    vmstat->mem->reg.eax = (uint32_t)((int32_t)vmstat->mem->reg.ebx + (int32_t)vmstat->mem->reg.eax);
    vmstat->pc += 1;
}

void subOp(vmstat* vmstat){
    vmstat->mem->reg.eax = (int32_t)vmstat->mem->reg.eax - (int32_t)vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void mulOp(vmstat* vmstat){
    vmstat->mem->reg.eax =  (uint32_t)((int32_t)vmstat->mem->reg.eax * (int32_t)vmstat->mem->reg.ebx);
    vmstat->pc += 1;
}

void divOp(vmstat* vmstat){
    if(vmstat->mem->reg.ebx == 0){
        fprintf(stderr, "Error: Division by zero\n");
        exit(1);
    }

    vmstat->mem->reg.eax = (uint32_t)((int32_t)vmstat->mem->reg.eax / (int32_t)vmstat->mem->reg.ebx);
    vmstat->mem->reg.edx = (uint32_t)((int32_t)vmstat->mem->reg.eax % (int32_t)vmstat->mem->reg.ebx);
    vmstat->pc += 1;
}

void andOp(vmstat* vmstat){
    vmstat->mem->reg.eax &= vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void orOp(vmstat* vmstat){
    vmstat->mem->reg.eax |= vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void xorOp(vmstat* vmstat){
    vmstat->mem->reg.eax ^= vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void notOp(vmstat* vmstat){
    vmstat->mem->reg.eax = ~vmstat->mem->reg.eax;
    vmstat->pc += 1;
}

void uaddOp(vmstat* vmstat){
    vmstat->mem->reg.eax += vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void usubOp(vmstat* vmstat){
    vmstat->mem->reg.eax -= vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void umulOp(vmstat* vmstat){
    vmstat->mem->reg.eax *= vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}

void udivOp(vmstat* vmstat){
    if(vmstat->mem->reg.ebx == 0){
        fprintf(stderr, "Error: Division by zero\n");
        exit(1);
    }

    vmstat->mem->reg.eax = vmstat->mem->reg.eax / vmstat->mem->reg.ebx;
    vmstat->mem->reg.edx = vmstat->mem->reg.eax % vmstat->mem->reg.ebx;
    vmstat->pc += 1;
}