%include "ärt_utils.inc"
    global print_str

		EXTERN str_length

;
; rcx: string buffer
;
print_str:

    enter 0, 0
		pushall

		call str_length
		mov rdx, rax

		xor rdi,rdi		; stdout
		mov rsi, rcx	; buf
		xor rdx, 0    ; size
		mov rax, 1		; sys_write
		syscall

		popall
		leave
    ret
