#include "include/kernel.h"

namespace DmNSOS {
    void fs_init(void) {
        
    }

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
//        fs_init();
        println_string("TODO: FileSystem!");
        //
        asm("sti");
        while (1);
    }
}