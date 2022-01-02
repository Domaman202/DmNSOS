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

    while (1) {
        print_string("> ");

        char *line = readline();
        if (!strlen(line))
            continue;

        if (strcmp(line, "clear") == 0) {
            vga_clear_buffer();
            continue;
        } else if (strcmp(line, "test") == 0) {
            uint8_t bc[] = {
                    0x8b, 0x44, 0x24, 0x04,
                    0x03, 0x44, 0x24, 0x08,
                    0xc3
            };
            void *ptr = calloc(sizeof(bc), sizeof(uint8_t));
            memcpy(ptr, bc, sizeof(bc));
            int (*foo)(int, int) = ptr;
            char l[80];
            println_string(itoa(l,(*foo)(2, 3)));
            free(ptr);
        } else if (strcmp(line, "exit") == 0) {
            while (1)
                for (uint16_t i = 0; i < vga_w * vga_h; i++)
                    vga_buffer[i] = rand();
        } else if (strcmp(line, "memory") == 0) {
            char l[80];
            print_stringc("[MEMORY] [Start> ", 0x14);
            println_stringc(itoa(l, (uintptr_t) MEM_START), 0x12);
            print_stringc("[MEMORY] [End>   ", 0x14);
            println_stringc(itoa(l, (uintptr_t) MEM_END), 0x12);
            print_stringc("[MEMORY] [Space> ", 0x14);
            println_stringc(itoa(l, MEM_SPACE), 0x12);
        } else if (strcmp(line, "hello") == 0)
            println_stringc("Hello!", 0x15);
        else if (strcmp(line, "pit") == 0) {
            print_stringc("PIT => ", 0x1E);
            char l[80];
            println_stringc(itoa(l, PITCounter), 0x12);
        } else {
            print_stringc(line, 0x15);
            println_stringc(" <: not found", 0x1C);
        }

        free(line);
    }
}