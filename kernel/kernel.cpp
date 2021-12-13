#include "kernel.h"

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
    void* ptr0 = malloc(256);
    void* ptr1 = malloc(256);
    void* ptr2 = malloc(256);
    void* ptr3 = malloc(256);
    //
    char line[80];
    println_string(itoa(line, ptr0));
    println_string(itoa(line, ptr1));
    println_string(itoa(line, ptr2));
    println_string(itoa(line, ptr3));
    //
    free(ptr0);
    free(ptr1);
    free(ptr2);
    free(ptr3);
    //
    class test {
    public:
        void foo() {
            println_string("Foo!");
        }
    };
    //
    test obj;
    obj.foo();
    //
    println_string(itoa(line, sizeof(void*)));
    println_string(itoa(line, sizeof(uintptr_t)));
    //
    jmp_buf jmp_buf;
    int jmp_value;
    if ((jmp_value = setjmp(&jmp_buf)) == 0) {
        println_string("Jmp 0 value!");
        longjmp(&jmp_buf, 12);
        println_string("Post jump code N0!"); // Not executable.
    } else {
        print_string("Jmp value => ");
        println_string(itoa(line, jmp_value));
    }
    println_string("Post jump code N1!"); // Two calls.
    if (jmp_value == 12)
        longjmp(&jmp_buf, 202);
    print_string("Post jump code N2!");
    //
    while (1);
}