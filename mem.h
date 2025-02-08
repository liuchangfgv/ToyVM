#ifndef MEM_H
#define MEM_H

#include <stdint.h>
#include "core.h"

void mov(vmstat* vmstat);
void push(vmstat* vmstat);
void pop(vmstat* vmstat);
void num(vmstat* vmstat);
void mov8(vmstat* vmstat);

#endif