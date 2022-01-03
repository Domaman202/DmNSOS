#include "inc/kernel.h"

// 33554616 33555648

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
        char *line = readline();

        if (strcmp(line, "hello") == 0) {
            println_stringc("Hello!", 0x15);
        } else if (strcmp(line, "scroll") == 0)
            vga_auto_scroll = !vga_auto_scroll;
        else if (strcmp(line, "info") == 0) {
            program_info();
        } else if (strcmp(line, "memory") == 0) {
            program_memory();
        } else if (strlen(line))
            println_stringc("[ERROR] !NOT FOUNDED PROGRAM! [ERROR]", 0x14);

        free(line);
    }
}

void program_memory(void) {
    mode:
    println_string("Select memory mode:\n0 - print space;\n1 - print blocks;\n2 - alloc/free.");
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
        mem_block *last_block = MEM_START;
        while (last_block != MEM_END) {
            print_stringc("Block #", 0x1D);
            print_stringc(itoa(l, i), 0x14);
            println_stringc(" info:", 0x1D);
            print_stringc("[size]>      ", 0x1B);
            println_stringc(itoa(l, last_block->size + sizeof(mem_block)), 0x12);
            print_stringc("[allocated]> ", 0x1B);
            println_stringc(itoa(l, last_block->size), 0x12);
            print_stringc("[flags]>     ", 0x1B);
            println_stringc(itoa(l, last_block->flags), 0x12);
            print_stringc("[start]>     ", 0x1B);
            println_stringc(itoa(l, last_block), 0x12);
            print_stringc("[end]>       ", 0x1B);
            println_stringc(itoa(l, (uintptr_t) last_block + last_block->size + sizeof(mem_block)), 0x12);
            last_block = (mem_block*) ((uintptr_t) last_block + last_block->size + sizeof(mem_block));
            i++;
        }
    } else if (c == '2') {
        mode0:
        println_string("Select allocation mode:\n0 - malloc;\n1 - calloc;\n2 - realloc;\n3 - free;\n4 - combine blocks.");
        char c0 = getchar();
        if (c0 == '0') {
            print_string("Size => ");
            char* str = readline();
            void *ptr = malloc(atoi(str));
            free(str);
            print_string("Address => ");
            char line[80];
            println_string(itoa(line, ptr));
        } else if (c0 == '1') {
            print_string("Count => ");
            char* str = readline();
            int i = atoi(str);
            free(str);
            print_string("Size => ");
            str = readline();
            void *ptr = calloc(i, atoi(str));
            free(str);
            print_string("Address => ");
            char line[80];
            println_string(itoa(line, ptr));
        } else if (c0 == '2') { // TODO:
            println_stringc("!WIP!", 0x04);
//            print_string("Memory => ");
//            char* str = readline();
//            void* i = (uintptr_t) atoi(str);
//            free(str);
//            print_string("Size => ");
//            str = readline();
//            void *ptr = realloc(i, atoi(str));
//            free(str);
//            print_string("Address => ");
//            char line[80];
//            println_string(itoa(line, (uintptr_t) ptr - sizeof(mem_block)));
        } else if (c0 == '3') {
            print_string("Memory => ");
            char* str = readline();
            free(atoi(str));
            free(str);
        } else if (c0 == '4') { // TODO:
            println_stringc("!WIP!", 0x04);
//            print_string("Memory => ");
//            char* str = readline();
//            mem_block *block = atoi(str) - sizeof(mem_block);
//            free(str);
//            mem_block *next_block = block;
//            while (next_block->flags == 0x0 || next_block != MEM_END)
//                next_block = (mem_block*) ((uintptr_t) block + block->size + sizeof(mem_block));
//            block->size = (uintptr_t) next_block - (uintptr_t) block;
        } else goto mode0;
    } else goto mode;
}

void program_info(void) {
    println_stringc("Authors:", 0x17);
    println_stringc("Pavel Kuchaev", 0x18);
    println_stringc("Dmitry Pashkov", 0x18);
    println_stringc("Lev Koporushkin", 0x18);
}