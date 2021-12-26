[bits 32]

; Check A20 line
; Returns to caller if A20 gate is cleared.
; Continues to A20_on if A20 line is set.
; Written by Elad Ashkcenazi

[global check_A20line]
check_A20line:
	pushad
	mov edi,0x112345  	;odd megabyte address.
	mov esi,0x012345  	;even megabyte address.
	mov [esi],esi     	;making sure that both addresses contain diffrent values.
	mov [edi],edi     	;(if A20 line is cleared the two pointers would point to the address 0x012345 that would contain 0x112345 (edi))
	cmpsd             	;compare addresses to see if the're equivalent.
	popad
	mov ax, 1
	jne check_A20_exit 	;if not equivalent , A20 line is set.
	mov ax, 0
	check_A20_exit:
	ret

[global enable_A20line]
enable_A20line:
        cli

        call    a20wait
        mov     al,0xAD
        out     0x64,al

        call    a20wait
        mov     al,0xD0
        out     0x64,al

        call    a20wait2
        in      al,0x60
        push    eax

        call    a20wait
        mov     al,0xD1
        out     0x64,al

        call    a20wait
        pop     eax
        or      al,2
        out     0x60,al

        call    a20wait
        mov     al,0xAE
        out     0x64,al

        call    a20wait
        sti
        ret

a20wait:
        in      al,0x64
        test    al,2
        jnz     a20wait
        ret


a20wait2:
        in      al,0x64
        test    al,1
        jz      a20wait2
        ret
