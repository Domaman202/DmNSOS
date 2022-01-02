[bits 32]

[global main]
main:
    [extern kmain]
    jmp kmain

%include "int.asm"