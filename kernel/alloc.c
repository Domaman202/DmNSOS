#include "alloc.h"
#include "screen.h"

void mem_init(void) {
    mem_block* block = (mem_block*) MEM_START;
    block->flags = 0x0;
    block->next = MEM_END;
}

size_t mb_size(mem_block* block) {
    return (long) block - (long) block->next;
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

//void* realloc(void* mem, size_t size) { TODO: fix
//    mem_block *block = ((uintptr_t) mem - sizeof(mem_block));
//    size_t bsize = mb_size(block);
//    char line[80];
//    println();
//    println_string(itoa(line, bsize));
//    println();
//    if (bsize == size)
//        return mem;
//    if (bsize < size) {
//        size_t free_space = bsize - size;
//        if (free_space > sizeof(mem_block)) {
//            mem_block *old_next = block->next;
//            mem_block *free_block = (uintptr_t) block + bsize - free_space;
//            free_block->flags = 0x0;
//            free_block->next = old_next;
//            block->next = free_block;
//            return mem;
//        } else return mem;
//    }
//    //
//    size_t i = 0;
//    size_t j = 0;
//    mem_block *last_block = block->next;
//    while (last_block->flags == 0x0) {
//        i++;
//        j += mb_size(last_block);
//        last_block = last_block->next;
//    }
//    if (j == size - bsize) {
//        block->next = last_block;
//        return mem;
//    } else if (j > size - bsize) {
//        if (sizeof(mem_block) < size - bsize) {
//            block->next = last_block;
//            return mem;
//        }
//        mem_block *old_next = last_block;
//        last_block = last_block - mb_size(last_block); // getting prev block
//        mem_block *free_block = old_next - (j - size - bsize);
//        free_block->flags = 0x0;
//        free_block->next = old_next;
//        last_block->next = free_block;
//        return mem;
//    }
//    //
//    void* new_mem = malloc(size);
//    memcpy(new_mem, mem, size);
//    block->flags = 0x0;
//    return new_mem;
//}

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