#include "inc/kernel.h"

void kmain() {
    vga_init();
    idt_init();
    mem_init();

    asm("sti");

    println_string("/=>DmN<=\\");
    println_string("/=> - <=\\");
    println_string("/=>SOS<=\\");

    while (1) {
        print_string("> ");
        char *line = readline();

        if (strcmp(line, "exit") == 0) {
            return;
        } else if (strcmp(line, "hello") == 0)
            println_stringc("Hello!", 0x03);
        else {
            print_stringc(line, 0x70);
            println_stringc(" <: not found", 0x0C);
        }
    }
}