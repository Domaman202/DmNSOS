#ifndef __ALLOC_H_
#define __ALLOC_H_

#include "stdint.h"

#define MEM_START ((void *) 0x2000000)
#define MEM_SPACE (80000)
#define MEM_END (MEM_START + MEM_SPACE)

typedef struct mem_block {
    uint8_t flags;
    uint32_t size;
} mem_block;

void mem_init(void);

//void* realloc(void*, size_t);
void* calloc(size_t num, size_t size);
void* malloc(size_t);
void free(void*);

#endif //__ALLOC_H_