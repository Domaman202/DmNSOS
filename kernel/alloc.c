#include "alloc.h"

void mem_init(void) {
    mem_block* block = (mem_block*) MEM_START;
    block->flags = 0x0;
    block->next = MEM_END;
}

size_t mb_size(mem_block* block) {
    return block->next - block;
}

mem_block* split_heap(size_t size) {
    mem_block* last_block = (mem_block*) MEM_START;
    while (last_block->flags == 0x1)
        last_block = last_block->next;

    if (mb_size(last_block) == size) {
        last_block->flags = 0x1;
        return last_block;
    }

    last_block->flags = 0x1;

    mem_block* new_next_block = (mem_block*)((uintptr_t) last_block + size + sizeof(mem_block));
    new_next_block->next = last_block->next;
    last_block->next = new_next_block;

    return last_block;
}

void* calloc(size_t num, size_t size) {
    uint64_t i = num * size;
    uint8_t* mem = malloc(i);
    for (i--; i != -1; i--)
        mem[i] = 0;
}

void* malloc(size_t size) {
    return split_heap(size) + sizeof(mem_block);
}

void free(void* ptr) {
    ((mem_block*) ((uintptr_t) ptr - sizeof(mem_block)))->flags = 0x0;
}