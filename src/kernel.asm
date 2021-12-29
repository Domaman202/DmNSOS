section .text
	use16
_start:
	mov ax, cs
	mov ds, ax

	mov si, message
	cld
	mov ah, 0x0E
	mov bh, 0x00
puts_loop:
	lodsb
	test al, al
	jz puts_loop_exit
	int 0x10
	jmp puts_loop
puts_loop_exit:
	jmp $

message:
	db 'Hello, World!', 0
