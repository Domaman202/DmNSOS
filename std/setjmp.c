#include "setjmp.h"

int setjmp(jmp_buf* buf) {
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
void longjmp(jmp_buf* buf, int val) {
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
