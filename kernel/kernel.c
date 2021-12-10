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

    //
    while (1);
}

/*
char* message0 = malloc(8);
    message0[0] = 'H';
    message0[1] = 'e';
    message0[2] = 'l';
    message0[3] = 'l';
    message0[4] = 'o';
    message0[5] = ',';
    message0[6] = ' ';
    message0[7] = '\0';
    //
    print_string(message0);
    free(message0);
    //
    char* message1 = malloc(7);
    message1[0] = 'C';
    message1[1] = 'a';
    message1[2] = '/';
    message1[3] = '\\';
    message1[4] = 'o';
    message1[5] = '!';
    message1[6] = '\0';
    free(message1);
    //
    println_string(message1);
 */