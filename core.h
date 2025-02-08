#ifndef CORE_H
#define CORE_H

#include <stdint.h>
#include <stdbool.h>

#include "rom.h"

typedef struct functionStack{
    uint32_t p;
    uint32_t stack[1024];
}functionStack;

typedef struct vmstat{
    mem *mem;
    int32_t pc;
    uint32_t function_id;
    functionStack *functionStack;
    uint32_t stack_pointer;
    codes **codes;
    uint32_t code_size;
    struct{
        bool bigthen;
        bool smallthan;
        bool equal;
    }eflags;
    bool done;
}vmstat;

#define OPCODE(addr) (((codes *)vmstat->codes[vmstat->function_id])->code[addr])

#endif