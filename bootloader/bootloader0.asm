ORG 0x7C00
jmp 0x0000:start

; Start execution

start:
;xor ax, ax
    mov ax, 0
    mov ds, ax
    mov es, ax
; Load the second stage
; load AL sectors to ES:BX from drive DL
    mov bx, 0x7C00 + 512
    
    push dx
    mov ah, 0x02 ; 0x13 read sector
    
    mov al, 1 ; how many sectors to read
    mov ch, 0 ; cylinder 0
    mov dh, 0 ; head 0
    mov cl, 2 ; start at sector 2 (1 is boot sector)

    int 0x13
    
    pop dx

    mov bx, 0x07c0
    mov es, bx
    mov bx, 0x200
    push es
    push bx
    retf
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55