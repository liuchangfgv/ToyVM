#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdint.h>

#include "core.h"
#include "mem.h"

void call(vmstat* vmstat);
void ret(vmstat* vmstat);

#endif