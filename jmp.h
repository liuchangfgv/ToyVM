#ifndef JMP_H
#define JMP_H

#include "core.h"

void jmp(vmstat* vmstat);
void jz(vmstat* vmstat);
void jnz(vmstat* vmstat);
void je(vmstat* vmstat);
void jne(vmstat* vmstat);
void jg(vmstat* vmstat);
void jge(vmstat* vmstat);
void jl(vmstat* vmstat);
void jle(vmstat* vmstat);
void cmp(vmstat* vmstat);

#endif