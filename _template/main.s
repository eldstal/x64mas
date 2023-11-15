%include "ärt.inc"


    SECTION .data

stilla_natt:
    db "Stilla natt"
		db 0xa
		db 0



    SECTION .text
    global _start

_start:
		mov rcx, stilla_natt
    call print_str

		mov rax, 60	; sys_exit
		mov rdi, 0	; status
		syscall
