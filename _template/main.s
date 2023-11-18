%include "ärt.inc"


		SECTION .data

stilla_natt:
    db "Stilla natt"
newline:
    db 0xa
    db 0



    SECTION .text
    global _start

_start:
    mov rcx, stilla_natt
    call print_str

		mov rcx, 1234
		mov rdx, 10
		call print_int

    mov rcx, newline
    call print_str

		mov rcx, 0xdeadbeef
		mov rdx, 16
		call print_int

    mov rcx, newline
    call print_str

		mov rcx, 0xdeadbeef
		mov rdx, 2
		call print_int

    mov rcx, newline
    call print_str

    mov rax, 60 ; sys_exit
    mov rdi, 0  ; status
    syscall
