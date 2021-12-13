#ifndef ALLOC_H
#define ALLOC_H

#include "stdint.h"

#define MEM_START ((void *) 0x2000000)
#define MEM_SPACE 536870912
#define MEM_END MEM_START + MEM_SPACE

typedef struct mem_block {
    uint8_t flags;
    struct mem_block* next;
} mem_block;

void mem_init(void);
size_t mb_size(mem_block* mem_block);
mem_block* split_heap(size_t size);
void* malloc(size_t size);
void free(void* ptr);

#endif //ALLOC_H