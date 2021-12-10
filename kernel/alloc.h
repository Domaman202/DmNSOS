#ifndef ALLOC_H
#define ALLOC_H

#include "stdlib.h"

typedef struct mem_block_header {
    size_t size;
    int free;
    struct mem_block_header *next;
    struct mem_block_header *prev;
} mem_block_header;

mem_block_header* mem_start_block;

void mem_init() {
    mem_start_block = (mem_block_header*) MEM_SPACE;
    mem_start_block->free = 1;//if free 1,if allocated 0
    mem_start_block->size = 25000 - sizeof(mem_block_header);
    mem_start_block->prev = 0;
    mem_start_block->next = 0;
}

mem_block_header *newdata(mem_block_header *block, size_t size, size_t freesize) {
    mem_block_header *newdata = (mem_block_header *)((char *)block + size + sizeof(mem_block_header) + 1);
    newdata->size = freesize - size - sizeof(mem_block_header) - 1;
    newdata->free = 1;
    newdata->next = block->next;
    newdata->prev = block;
    return newdata;
}

void* malloc(size_t size) {
    mem_block_header *travel = mem_start_block;
    while (1) {
        if (travel == 0)
            return 0;
        else if (travel->size >= (size + sizeof(mem_block_header)) && travel->free == 1) {
            travel->next = newdata(travel, size, travel->size);
            travel->size = size;
            travel->free = 0;
            break;
        }
        travel = travel->next;
    }
    return (char *) travel + sizeof(mem_block_header) + 1;
}

void free(void *ptr) {
    mem_block_header *info = (mem_block_header *) ((char *) ptr - 1) - 1;
    info->free = 1;
    if (info->next != 0 && info->next->free == 1) {
        info->size += info->next->size + sizeof(mem_block_header) + 1;
        if (info->next->next != 0)
            info->next->next->prev = info;
        info->next = info->next->next;
    }

    if (info->prev != 0 && info->prev->free == 1) {
        info->prev->size += info->size + sizeof(mem_block_header) + 1;
        if (info->next != 0)
            info->next->prev = info->prev;
        info->prev->next = info->next;
    }
}

#endif //ALLOC_H