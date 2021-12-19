#ifndef __ALLOC_H_
#define __ALLOC_H_

#include "stdint.h"

#define MEM_START ((void *) 0x2000000)
#define MEM_SPACE 536870912
#define MEM_END MEM_START + MEM_SPACE

typedef struct mem_block {
    uint8_t flags;
    struct mem_block* next;
} mem_block;

void mem_init(void);
size_t mb_size(mem_block*);
mem_block* split_heap(size_t);
void* realloc(void* mem, size_t size);
void* calloc(size_t num, size_t size);
void* malloc(size_t);
void free(void*);

#endif //__ALLOC_H_