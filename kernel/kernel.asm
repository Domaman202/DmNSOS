[global main]
main:
    [bits 32]
    [extern kmain]
    jmp kmain

%include "a20line.asm"
%include "int.asm"
