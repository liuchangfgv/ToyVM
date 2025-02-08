#ifndef ALU_H
#define ALU_H

#include "core.h"

void addOp(vmstat* vmstat);
void subOp(vmstat* vmstat);
void mulOp(vmstat* vmstat);
void divOp(vmstat* vmstat);
void andOp(vmstat* vmstat);
void orOp(vmstat* vmstat);
void xorOp(vmstat* vmstat);
void notOp(vmstat* vmstat);
void uaddOp(vmstat* vmstat);
void usubOp(vmstat* vmstat);
void umulOp(vmstat* vmstat);
void udivOp(vmstat* vmstat);

#endif