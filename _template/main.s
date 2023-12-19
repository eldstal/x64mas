%include "ärt.inc"


		SECTION .data

stilla_natt:
    db "Stilla natt"
newline:
    db 0xa
nostring:
    db 0

csv:
    db "one,two 2,three,,five"
    db 0
csv_out:
    times 32 dq 0

inbuf:
    times 16 db 0


    SECTION .text
    global _start

_start:
    mov rcx, stilla_natt
    call print_str

		mov rcx, stilla_natt
    call str_length

    mov rcx, rax
		mov rdx, 10
		call print_int
    call print_newline

		mov rcx, nostring
    call str_length

    mov rcx, rax
		mov rdx, 10
		call print_int
    call print_newline

		mov rcx, 0xdeadbeef
		mov rdx, 16
		call print_int
    call print_newline

		mov rcx, 0xdeadbeef
		mov rdx, 2
		call print_int
    call print_newline

    mov rcx, 0x2F
    call is_digit
    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline


    mov rcx, "0"
    call is_digit
    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline

    mov rcx, "9"
    call is_digit
    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline

    mov rcx, 0x3A
    call is_digit
    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline


    ;
    ; str_split
    ;
    mov rcx, csv
    mov rdx, ","
    mov r8, csv_out
    mov r9, 3
    call str_split

    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline

    mov rdi, csv_out
    split_loop:

      mov rax, [rdi]
      test rax, rax
      jz split_done

      mov rcx, rax
      call print_str
      call print_newline

      add rdi, 8
      jmp split_loop

    split_done:


    ;
    ; read_line
    ;
    mov rcx, 0    ; stdin
    mov rdx, inbuf
    mov r8, 16
    call read_line

    mov rcx, rax
    mov rdx, 16
    call print_int
    call print_newline

    mov rcx, inbuf
    call print_str
    call print_newline



    mov rax, 60 ; sys_exit
    mov rdi, 0  ; status
    syscall
