#include "kernel.h"

void kmain(void) {
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
    void* ptr0 = malloc(256);
    void* ptr1 = malloc(256);
    void* ptr2 = malloc(256);
    void* ptr3 = malloc(256);
    //
    char line[80];
    println_string(itoa(line, ptr0));
    println_string(itoa(line, ptr1));
    println_string(itoa(line, ptr2));
    println_string(itoa(line, ptr3));
    //
    free(ptr0);
    free(ptr1);
    free(ptr2);
    free(ptr3);
    //
    while (1);
}