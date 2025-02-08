#ifndef IO_H
#define IO_H

#include <stdint.h>
#include <stdbool.h>

#include "core.h"

void outstr(vmstat* vmstat);
void instr(vmstat* vmstat);
void innum(vmstat* vmstat);
void outnum(vmstat* vmstat);

#endif