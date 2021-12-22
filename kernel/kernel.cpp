#include "include/kernel.h"

extern "C" void __cxa_pure_virtual() {
    println_string("Called pure virtual function!");
}

namespace DmNSOS {
    extern "C" __attribute__((noreturn)) void kmain(void) {
        mem_init();
        init_vga();
        idt_init();

        println_string("/=>DmN<=\\");
        println_string("/=> - <=\\");
        println_string("/=>SOS<=\\");
        println_string("Version 0.2");
        while (1) {
            print_string("> ");
            char *line = readline();
            vga_nln();

            if (strcmp(line, "exit") == 0)
                break;
            else if (strcmp(line, "hello") == 0)
                println_string("Hello!");
            else if (strcmp(line, "test") == 0)
                test();
            else {
                print_string(line);
                println_string(" <: not found");
            }

            free(line);
        }
    }
}