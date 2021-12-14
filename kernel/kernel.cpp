#include "kernel.h"

extern "C" void kmain(void) {
    //
    init_vga();
    println_string("VGA initialized!");
    //
    idt_init();
    println_string("IDT initialized!");
    //
    mem_init();
    println_string("Memory initialized!");
    //
    char line[80];
    //
    void *ptr4 = malloc(256);
    println_string(itoa(line, mb_size((mem_block*) ((uintptr_t) ptr4 - sizeof(mem_block)))));
    ptr4 = realloc(ptr4, 128);
    println_string(itoa(line, mb_size((mem_block*) ((uintptr_t) ptr4 - sizeof(mem_block)))));
    ptr4 = realloc(ptr4, 256);
    println_string(itoa(line, mb_size((mem_block*) ((uintptr_t) ptr4 - sizeof(mem_block)))));
    ptr4 = realloc(ptr4, 512);
    println_string(itoa(line, mb_size((mem_block*) ((uintptr_t) ptr4 - sizeof(mem_block)))));
    //
    while (1);
}