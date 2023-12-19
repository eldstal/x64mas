%include "ärt.inc"


	SECTION .data

hack_completed:
    db "HACK SUCCESSFUL", 0x0a, 0x00
super_error:
    db "No good!!", 0x0a, 0x00
inbuf:
    times 256 db 0


    SECTION .text
    global _start

_start:

    xor r15,r15         ; total, our answer, the solution

    input_loop:
        mov rcx, 0
        mov rdx, inbuf
        mov r8, 256
        call read_line
        cmp rax, 0
        jl fail
        je done

        xor r14, r14    ; The identified number of the current line
        mov rdi, inbuf  ; input pointer

        
        call find_digit
        cmp rax, 0
        jl fail



        ; Set first found digit (in both positions)
        mov r13, rax        ; ones
        mov rbx, 10
        mul rbx
        mov r14, rax        ; tens
        
        
        
        singles_loop:
            call find_digit
            cmp rax, 0
            jl singles_done
            mov r13, rax
            jmp singles_loop

        singles_done:

        ; Add to the final sum!!
        add r15, r13
        add r15, r14



        jmp input_loop
    

    done:
    mov rcx, hack_completed
    call print_str
    jmp end

    fail:
    mov rcx, super_error
    call print_str


    end:

    mov rcx, r15
    mov rdx, 10
    call print_int
    call print_newline

    mov rax, 60 ; sys_exit
    mov rdi, 0  ; status
    syscall


; rdi: starting pointer
; rcx: clobbered
; returns numeric value in rax or -1 if end of string
find_digit:
    push rcx
    find_digit_loop:

        mov cl, [rdi]
        mov rax, -1     ; end of string
        cmp rcx, 0
        je find_digit_done

        inc rdi

        call is_digit
        cmp rax, 0
        jge find_digit_done

        jmp find_digit_loop     ; not a digit, keep trying


    find_digit_done:
    pop rcx
    ret