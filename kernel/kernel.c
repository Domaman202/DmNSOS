#include "inc/kernel.h"

__attribute__((__noreturn__, gnu_inline))
inline void kmain() {
    vga_init();
    idt_init();
    mem_init();

    asm("sti");

    println_string(" /=========\\");
    println_string("/=\\  DmN  /=\\");
    println_string("|=|   -   |=|");
    println_string("\\=/  SOS  \\=/");
    println_string(" \\=========/");

    while (1) {
        print_string("> ");
        char* line = readline();

        if (strcmp(line, "hello") == 0) {
            println_stringc("Hello!", 0x15);
        } else if (strcmp(line, "info") == 0) {
            println_stringc("Authors:", 0x17);
            println_stringc("Pavel Kuchaev", 0x18);
            println_stringc("Dmitry Pashkov", 0x18);
            println_stringc("Lev Koporushkin", 0x18);
        } else if (strcmp(line, "memory") == 0) {
            program_memory();
        } else {
            println_stringc("[ERROR] !NOT FOUNDED PROGRAM! [ERROR]", 0x14);
        }

        free(line);
    }
}

void program_memory(void) {
    mode:
    println_string("Select memory mode:\n0 - print space;\n1 - print blocks.");
    char c = getchar();
    if (c == '0') {
        char l[80];
        print_stringc("[MEMORY] [Start> ", 0x14);
        println_stringc(itoa(l, (uintptr_t) MEM_START), 0x12);
        print_stringc("[MEMORY] [End>   ", 0x14);
        println_stringc(itoa(l, (uintptr_t) MEM_END), 0x12);
        print_stringc("[MEMORY] [Space> ", 0x14);
        println_stringc(itoa(l, MEM_SPACE), 0x12);
    } else if (c == '1') {
        char l[80];
        uint32_t i = 0;
        mem_block *last_block = (mem_block *) MEM_START;
        while (last_block != MEM_END) {
            print_stringc("Block #", 0x1D);
            print_stringc(itoa(l, i), 0x14);
            println_stringc(" info:", 0x1D);
            print_stringc("[size]>      ", 0x1B);
            println_stringc(itoa(l, mb_size(last_block)), 0x12);
            print_stringc("[allocated]> ", 0x1B);
            println_stringc(itoa(l, mb_size(last_block) - sizeof(mem_block)), 0x12);
            print_stringc("[flags]>     ", 0x1B);
            println_stringc(itoa(l, last_block->flags), 0x12);
            print_stringc("[start]>     ", 0x1B);
            println_stringc(itoa(l, last_block), 0x12);
            print_stringc("[end]>       ", 0x1B);
            println_stringc(itoa(l, last_block->next), 0x12);
            last_block = last_block->next;
            i++;
        }
    } else goto mode;
}