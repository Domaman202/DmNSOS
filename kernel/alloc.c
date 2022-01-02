#include "inc/string.h"
#include "inc/alloc.h"

void mem_init(void) {
    mem_block* block = (mem_block*) MEM_START;
    block->flags = 0x0;
    block->next = MEM_END;
}

int32_t mb_size(mem_block* block) {
    return (uintptr_t) block->next - (uintptr_t) block;
}

mem_block* split_heap(size_t size) {
    mem_block *last_block = (mem_block *) MEM_START;
    search:
    while (last_block->flags == 0x1)
        last_block = last_block->next;

    uint32_t last_block_size_for_alloc = mb_size(last_block) - sizeof(mem_block);

    if (last_block_size_for_alloc == size) {
        last_block->flags = 0x1;
        return last_block;
    }

    last_block->flags = 0x1;

    if (size < last_block_size_for_alloc) {
        mem_block *new_next_block = (mem_block *) ((uintptr_t) last_block + size + sizeof(mem_block));
        new_next_block->next = last_block->next;
        last_block->next = new_next_block;
    } else
        return (uintptr_t) realloc((uintptr_t) last_block + sizeof(mem_block), size) - sizeof(mem_block);
    return last_block;
}

void* realloc(void* mem, size_t size) {
    mem_block *block = ((uintptr_t) mem - sizeof(mem_block));
    size_t bsize = mb_size(block);
    if (bsize - sizeof(mem_block) == size)
        return mem;
    if (bsize > size) {
        size_t free_space = bsize - size - sizeof(mem_block);
        if (free_space > sizeof(mem_block)) {
            mem_block *old_next = block->next;
            mem_block *free_block = (uintptr_t) (block->next) - free_space;
            free_block->flags = old_next->flags;
            free_block->next = old_next->next;
            block->next = free_block;
            return mem;
        } else return mem;
    }
    //
    size_t i = 0;
    size_t j = 0;
    mem_block *last_block = block->next;
    while (last_block->flags == 0x0) {
        i++;
        j += mb_size(last_block);
        if (j == size - bsize) {
            block->next = last_block->next;
            return mem;
        }
        if (j > size - bsize) {
            size_t lbsize = mb_size(last_block);
            if (lbsize - (size - bsize) <= sizeof(mem_block)) {
                block->next = last_block->next;
                return mem;
            }
            mem_block* new_next = (uintptr_t) last_block + (size - bsize) + sizeof(mem_block);
            new_next->flags = 0x0;
            new_next->next = last_block->next;
            block->next = new_next;
            return mem;
        }
    }
    if (i == 0) {
        void *new_mem = malloc(size);
        memcpy(new_mem, mem, size);
        block->flags = 0x0;
        return new_mem;
    }
}

void* calloc(size_t num, size_t size) {
    uint64_t i = num * size;
    uint8_t* mem = malloc(i);
    memset(mem, 0, i);
    return mem;
}

void* malloc(size_t size) {
    return ((uintptr_t) split_heap(size)) + sizeof(mem_block);
}

void free(void* ptr) {
    ((mem_block *) ((uintptr_t) ptr - sizeof(mem_block)))->flags = 0x0;
}