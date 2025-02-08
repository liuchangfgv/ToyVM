#ifndef LOADER_H
#define LOADER_H

#include <stdio.h>
#include <stdlib.h>

#include "rom.h"

rom *loadFromFile(const char *filename,size_t *size);

#endif