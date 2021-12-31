#include "include/kernel.h"

void kmain() {
    init_vga();
    idt_init();
    mem_init();

    println_string("/=>DmN<=\\");
    println_string("/=> - <=\\");
    println_string("/=>SOS<=\\");
    while (1) {
        print_string("> ");
        char *line = readline();

        if (strcmp(line, "exit") == 0) {
            return;
        } else if (strcmp(line, "hello") == 0) {
            println_string("Hello!");
        } else {
            print_string(line);
            println_string(": not found");
        }
    }
}