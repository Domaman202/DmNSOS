[global main]
main:
    [bits 32]
    [extern kmain]
    jmp kmain

%include "int.asm"