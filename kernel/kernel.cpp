#include "kernel.h"

typedef struct {
    uint32_t ebx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t eip;
} jmp_buf;

// optimize("no-omit-frame-pointer") doesn't seem to work
// we still don't get a frame-point unless we force -O0 for the function with optimize(0)
__attribute__((noinline, noclone, returns_twice, optimize(0)))
int setjmp(void* var) {
    // relies on the compiler to make a stack-frame
    // because we're using inline asm inside a function instead of at global scope
    asm volatile(
    "    mov 8(%ebp), %eax     # get pointer to jmp_buf, passed as argument on stack\n"
    "    mov    %ebx, (%eax)   # jmp_buf[0] = ebx\n"
    "    mov    %esi, 4(%eax)  # jmp_buf[1] = esi\n"
    "    mov    %edi, 8(%eax)  # jmp_buf[2] = edi\n"
    "    mov    (%ebp), %ecx\n"
    "    mov    %ecx, 12(%eax) # jmp_buf[3] = ebp\n"
    "    lea    8(%ebp), %ecx  # get previous value of esp, before call\n"
    "    mov    %ecx, 16(%eax) # jmp_buf[4] = esp before call\n"
    "    mov    4(%ebp), %ecx  # get saved caller eip from top of stack\n"
    "    mov    %ecx, 20(%eax) #jmp_buf[5] = saved eip\n"
    "    xor    %eax, %eax     #eax = 0\n"
    );

    return 0;
}

__attribute__((noinline, noclone, optimize(0)))
void longjmp(void* var,int m) {
    asm volatile(
    "    mov  8(%ebp),%edx # get pointer to jmp_buf, passed as argument 1 on stack\n"
    "    mov  12(%ebp),%eax #get int val in eax, passed as argument 2 on stack\n"
    "    test    %eax,%eax # is int val == 0?\n"
    "    jnz 1f\n"
    "    inc     %eax      # if so, eax++\n"
    "1:\n"
    "    mov   (%edx),%ebx # ebx = jmp_buf[0]\n"
    "    mov  4(%edx),%esi # esi = jmp_buf[1]\n"
    "    mov  8(%edx),%edi #edi = jmp_buf[2]\n"
    "    mov 12(%edx),%ebp # ebp = jmp_buf[3]\n"
    "    mov 16(%edx),%ecx # ecx = jmp_buf[4]\n"
    "    mov     %ecx,%esp # esp = ecx\n"
    "    mov 20(%edx),%ecx # ecx = jmp_buf[5]\n"
    "    jmp *%ecx         # eip = ecx");
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
    println_string("Post jump code N1!");
    //
    while (1);
}