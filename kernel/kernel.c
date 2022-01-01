#include "inc/kernel.h"

__attribute__((__noreturn__, gnu_inline))
inline void kmain() {
    vga_init();
    idt_init();
    mem_init();

    asm("sti");

    println_string(" /=========\\");
    println_string("/=>  DmN  <=\\");
    println_string("|=>   -   <=|");
    println_string("\\=>  SOS  <=/");
    println_string(" \\=========/");

    char line[80];

    print_stringc("[MEMORY] [Start> ", 0x14);
    println_stringc(itoa(line, (uintptr_t) MEM_START), 0x12);
    print_stringc("[MEMORY] [End>   ", 0x14);
    println_stringc(itoa(line, (uintptr_t) MEM_END), 0x12);
    print_stringc("[MEMORY] [Space> ", 0x14);
    println_stringc(itoa(line, MEM_SPACE), 0x12);

    while (1) {
        print_string("> ");

        char *line = readline();
        if (!strlen(line))
            continue;

        if (strcmp(line, "clear") == 0) {
            vga_clear_buffer();
            continue;
        } else if (strcmp(line, "hello"))
            println_stringc("Hello!", 0x15);
        else if (strcmp(line, "pit")) {
            print_stringc("PIT => ", 0x1E);
            println_stringc(itoa(line, PITCounter), 0x12);
        } else {
            print_stringc(line, 0x15);
            println_stringc(" <: not found", 0x1C);
        }

        free(line);
    }
}