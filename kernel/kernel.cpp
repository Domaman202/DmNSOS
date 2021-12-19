#include "include/kernel.h"

namespace DmNSOS {
    extern "C" void kmain() {
        init_vga();
        idt_init();
        mem_init();

        println_string("DmNSOS");
        println_string("Version 0.1");
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
}