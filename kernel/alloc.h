#ifndef ALLOC_H
#define ALLOC_H

#include "stdlib.h"

typedef struct mem_block_header {
    /*
     * 0 - free
     * 1 - allocated
     */
    uint8_t flags;
    struct mem_block_header *next;
} mem_block_header;

mem_block_header* mem_start_block;

void mem_init() {
    mem_start_block = MEM_START;
    mem_start_block->flags = 0x0;
    mem_start_block->next = MEM_END;
}

mem_block_header* mem_split(size_t size) {
    mem_block_header* free_block = mem_start_block;
    while(free_block->flags == 0x1 && (free_block->next - free_block) != size) {
        if (free_block == MEM_END) {
            println_string("Tb| wo 9e6u/\\?!");
            return 0;
        }
        free_block = free_block->next;
    }
    if ((free_block->next - free_block) == size) {
        free_block->flags = 0x1;
        return free_block;
    }
    //
    mem_block_header* allocated_block = free_block;
    allocated_block->flags = 0x1;
    //
    mem_block_header* new_block = free_block + sizeof(mem_block_header) + size;
    new_block->flags = 0x0;
    new_block->next = allocated_block->next;
    //
    allocated_block->next = new_block;
    //
    return allocated_block;
}

void* malloc(size_t size) {
    return (void*) mem_split(size) + sizeof(mem_block_header);
}

void free(void *ptr) {
    ((mem_block_header*) ptr - sizeof(mem_block_header))->flags = 0x0;
}

void free_block(mem_block_header *ptr) {
    ptr->flags = 0x0;
}

#endif //ALLOC_H