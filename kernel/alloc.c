#include "inc/string.h"
#include "inc/alloc.h"

void mem_init(void) {
    mem_block* block = (mem_block*) MEM_START;
    block->flags = 0x0;
    block->size = (MEM_SPACE - sizeof(mem_block));
}

void* calloc(size_t num, size_t size) {
    uint64_t i = num * size;
    uint8_t* mem = malloc(i);
    memset(mem, 0, i);
    return mem;
}

void* malloc(size_t size) {
    mem_block *block = MEM_START;
    while (block->flags != 0x0 || block->size < size)
        block = (mem_block*) ((uintptr_t) block + sizeof(mem_block) + block->size);

    if (block->size != size && block->size > 9) {
        size_t free_space = block->size - size - sizeof(mem_block);
        uint8_t flags = ((mem_block *) ((uintptr_t) block + sizeof(mem_block) + block->size))->flags;
        mem_block *nblock = (uintptr_t) block + sizeof(mem_block) + (block->size = size);
        nblock->flags = flags;
        nblock->size = free_space;
    }

    block->flags = 0x1;
    return (uintptr_t) block + sizeof(mem_block);
}

void free(void* ptr) {
    ((mem_block *) ((uintptr_t) ptr - sizeof(mem_block)))->flags = 0x0;
}