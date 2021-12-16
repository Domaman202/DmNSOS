#include "include/kernel.h"

extern "C" void __cxa_pure_virtual() {
    println_string("Called pure virtual function!");
}

namespace DmNSOS {
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
        println_string("TODO: FileSystem!"); // TODO:
        //
        class A {
        public:
            A() {
                println_string("A Constructor!");
            }

            ~A() {
                println_string("A Destructor!");
            }

            virtual void foo() = 0;
        };
        class B : public A {
        public:
            B() {
                println_string("B Constructor!");
            }

            ~B() {
                println_string("B Destructor!");
            }

            virtual void foo() override {
                println_string("Foo!");
            }
        };
        //
        A* obj = malloc(sizeof(A));
        new (obj) B();
        obj->foo();
        delete obj;
        //
        test();
        //
        asm("sti");
        while (1);
    }
}