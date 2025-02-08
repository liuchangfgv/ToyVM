#include <stdint.h>
#include "core.h"
#include "function.h"

void call(vmstat* vmstat){
    int32_t addr = vmstat->pc+1;

    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->function_id;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->pc+2;

    //save registers
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.eax;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.ebx;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.ecx;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.edx;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.esi;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.edi;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.eip;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->mem->reg.esp;
    vmstat->functionStack->stack[vmstat->functionStack->p++] = vmstat->stack_pointer;

    vmstat->function_id = OPCODE(addr);
    vmstat->pc = 0;
}

void ret(vmstat* vmstat){
    if(vmstat->functionStack->p == 0){
        vmstat->done = true;
        return;
    }

    //restore registers
    vmstat->stack_pointer = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.esp = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.eip = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.edi = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.esi = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.edx = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.ecx = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.ebx = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->mem->reg.eax = vmstat->functionStack->stack[--vmstat->functionStack->p];

    vmstat->pc = vmstat->functionStack->stack[--vmstat->functionStack->p];
    vmstat->function_id = vmstat->functionStack->stack[--vmstat->functionStack->p];
}
