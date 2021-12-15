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
    while (1);
}