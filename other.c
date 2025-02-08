#include "core.h"
#include "other.h"

void nop(vmstat* vmstat){
    // do nothing
    vmstat->pc += 1;
}