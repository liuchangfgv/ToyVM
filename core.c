#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rom.h"
#include "loader.h"
#include "core.h"
#include "alu.h"
#include "mem.h"
#include "function.h"
#include "jmp.h"
#include "io.h"
#include "other.h"

#define DEBUG

void (*ops[])(vmstat* vmstat) = {
    nop,// 0
    addOp,// 1 EAX += EBX
    subOp,// 2 EAX -= EBX
    mulOp,// 3 (EAX , EBX) = EAX * EBX
    divOp,// 4 (EAX , EBX) = (EAX / EBX , EAX % EBX)
    andOp,// 5 EAX &= EBX
    orOp,// 6 EAX |= EBX
    xorOp,// 7  EAX |= EBX
    notOp,// 8 EAX = ~EAX
    uaddOp,// 9 unsignaled
    usubOp,// 10 unsignaled
    umulOp,// 11 unsignaled
    udivOp,// 12 unsignaled
    mov,// 13 [next opcode] = [next next opcode]
    push,// 14 [stack pointer++] = [next opcode]
    pop,// 15 [next opcode] = [--stack pointer]
    num,// 16 [next opcode] = next next opcode
    call,// 17
    ret,// 18
    jmp,// 19
    jz,// 20
    jnz,// 21
    je,// 22
    jne,// 23
    jg,// 24
    jge,// 25
    jl,// 26
    jle,// 27
    cmp,// 28
    outstr,// 29
    instr,// 30
    outnum,// 31
    innum,// 32
    mov8,// 33
};

void exec(vmstat* vmstat){
    vmstat->done = false;
    while(!vmstat->done){
        if(vmstat->function_id > vmstat->code_size){
            fprintf(stderr, "Error: Invalid function id at address 0x%x\n", vmstat->function_id);
            exit(1);
        }

        if(vmstat->pc >= (int32_t)((codes *)vmstat->codes[vmstat->function_id])->len){
            fprintf(stderr, "Error: Invalid program counter at address 0x%x\n", vmstat->pc);
            exit(1);
        }

        uint8_t opcode = ((codes *)vmstat->codes[vmstat->function_id])->code[vmstat->pc];
        
        if(opcode >= (sizeof(ops)/sizeof(ops[0]))){
            fprintf(stderr, "Error: Invalid opcode at address 0x%x\n", vmstat->pc);
            exit(1);
        }
        
        (*ops[opcode])(vmstat);

#ifdef DEBUG
        // print registers
        printf("EAX: %d\t", vmstat->mem->reg.eax);
        printf("EBX: %d\t", vmstat->mem->reg.ebx);
        printf("ECX: %d\t", vmstat->mem->reg.ecx);
        printf("EDX: %d\t", vmstat->mem->reg.edx);
        printf("ESI: %d\t", vmstat->mem->reg.esi);
        printf("EDI: %d\t", vmstat->mem->reg.edi);
        printf("EIP: %d\t", vmstat->mem->reg.eip);
        printf("ESP: %d\n", vmstat->mem->reg.esp);
        // print eflags
        printf("bigthen: %d\t", vmstat->eflags.bigthen);
        printf("smallthan: %d\t", vmstat->eflags.smallthan);
        printf("equal: %d\n", vmstat->eflags.equal);
#endif
    }
    return;
}

vmstat* initVmstat(rom* rom,size_t size){
    vmstat* vmstat = malloc(sizeof(struct vmstat));
    if(vmstat == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memset(vmstat, 0, sizeof(struct vmstat));

    vmstat->mem = malloc(sizeof(mem));
    if(vmstat->mem == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    memset(vmstat->mem, 0, sizeof(mem));

    vmstat->functionStack = malloc(sizeof(functionStack));
    if(vmstat->functionStack == NULL){
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    memcpy(vmstat->mem,(const void *)&rom->mem, rom->mem.reg.headerLen);
    vmstat->pc = 0;
    vmstat->functionStack->p = 0;
    vmstat->function_id = rom->mem.reg.eip;
    vmstat->stack_pointer = rom->mem.reg.esp;
    vmstat->done = false;

    size_t functions = 0;
    uint8_t *c = ((uint8_t *)rom) + rom->mem.reg.headerLen;
    while( (size_t)(c - (uint8_t*)rom) < size){
        codes *p = (codes *)c;
        functions ++;
        c += sizeof(codes) + p->len*sizeof(uint32_t);
    }

    vmstat->codes = malloc(sizeof(codes *) * functions);
    c = ((uint8_t *)rom) + rom->mem.reg.headerLen;
    for(size_t i=0; i<functions; i++){
        codes *p = (codes *)c;
        vmstat->codes[i] = malloc(sizeof(codes) + p->len*sizeof(uint32_t));
        memcpy(vmstat->codes[i], p, sizeof(codes) + p->len*sizeof(uint32_t));
        c += sizeof(codes) + p->len*sizeof(uint32_t);
    }
    vmstat->code_size = functions;

    return vmstat;
}

void freeVmstat(vmstat* vmstat){
    free(vmstat->mem);
    free(vmstat->functionStack);

    for(size_t i=0; i<vmstat->code_size; i++){
        free(vmstat->codes[i]);
    }
    free(vmstat->codes);
    free(vmstat);
    return;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    size_t size;
    rom *rom = loadFromFile(argv[1], &size);
    if(rom == NULL){
        return 1;
    }

    vmstat* vmstat = initVmstat(rom, size);
    exec(vmstat);
    freeVmstat(vmstat);
}