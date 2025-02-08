#ifndef ROM_H
#define ROM_H

#include <stdint.h>

typedef union mem{
    struct __attribute__((packed, aligned(1))) {
	    uint32_t eax;
		uint32_t ebx;
		uint32_t ecx;
		uint32_t edx;
		uint32_t esi;
		uint32_t edi;
		uint32_t eip; // eip
		uint32_t esp; // load stack pointer to here
		uint32_t headerLen; // size of header need load to memory
	} reg;
	uint32_t mem[0x10000]; // 256KB of memory ,first 36B is register area ,32bit mode
	uint8_t mem8[0x40000]; // 256kb of memory, first 36B is register area, 8bit mode
}mem;

typedef struct __attribute__((packed, aligned(1))) rom{
	mem mem;
	uint8_t codes[];// 弃用,因为mem存储的长度可变
}rom;

typedef struct __attribute__((packed, aligned(1))) codes{
    uint32_t len;
	uint32_t code[];
}codes;

#endif