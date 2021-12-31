ORG 0x7E00
jmp 0x0000:start

KERNEL_ADDRESS equ 0x8000
NUM_SECTORS equ 83

; GDT definitions
gdt_start:
gdt_null:
	dd 0x0
	dd 0x0
gdt_code:
	dw 0xffff		; Limit (bits 0-15)
	dw 0x0			; Base (bits 0-15)
	db 0x0			; Base (bits 16-23)
	db 10011010b		; 1st flags, access byte
	db 11001111b		; 2nd flags, Limit (bits 16-19)
	db 0x0			; Base (bits 24-31)
gdt_data:
	dw 0xffff		; Limit (bits 0-15)
	dw 0x0			; Base (bits 0-15)
	db 0x0			; Base (bits 16-23)
	db 10010010b		; 1st flags, type flags
	db 11001111b		; 2nd flags, Limit (bits 16-19)
	db 0x0			; Base (bits 24-31)
gdt_end:
gdt_descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
	
; Start execution

start:
	xor ax, ax
	mov ds, ax
	mov es, ax
; Set up the stack:
	cli
	mov bp, 0x7C00
	mov sp, bp
	mov ss, ax
	sti
; Store the boot drive for later:
	mov [BOOT_DRIVE], dl
; Load the kernel
	mov bx, KERNEL_ADDRESS
	mov dh, NUM_SECTORS 
	mov dl, [BOOT_DRIVE]
; load DH sectors to ES:BX from drive DL
; Add a looping thing here to load one sector at a time, rather than all at once?
	push dx
	mov ah, 0x02		; 0x13 read sector
;.load_loop:
	mov al, dh		; how many sectors to read
	mov ch, 0		; cylinder 0
	mov dh, 0		; head 0
	mov cl, 3		; start at sector 2 (1 is boot sector)
	int 0x13

	jc halt
	pop dx
	cmp dh, al
	jne halt
; Enter Protected Mode and jump to kernel
	cli
	lgdt [gdt_descriptor]	; defines protected mode segments
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

    ; flush the prefetch input queue
    ; Perform far jump to selector 08h (offset into GDT, pointing at a 32bit PM code segment descriptor) 
    ; to load CS with proper PM32 descriptor)
	jmp CODE_SEG:init_pm	; flushes real-mode commands

[BITS 32]
init_pm:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ebp, 0x90000
	mov esp, ebp

	jmp KERNEL_ADDRESS
	jmp $

[BITS 16]

halt:
    jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xaa55