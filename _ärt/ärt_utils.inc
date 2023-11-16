%macro pushall 0
    push rax
    push rbx
    push rsi
    push rdi
    push r10
    push r11
    push r12
    push r13
    push r14
    push r15
%endmacro

%macro popall 0
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push rdi
    push rsi
    push rbx
    push rax
%endmacro


; First argument is syscall number
; Return value in rax
%macro syscall6 7

    ; Save argument registers
    ; just so our clobbering will be
    ; consistent
    push rdi
    push rsi
    push rdx
    push r10
    push r8
    push r9

    ; Push so that we don't risk
    ; clobbering an input register
    ; when setting up syscall args
    push %7
    push %6
    push %5
    push %4
    push %3
    push %2

    mov rax, %1
    mov rdi, [rsp+0]
    mov rsi, [rsp+0x8]
    mov rdx, [rsp+0x10]
    mov r10, [rsp+0x18]
    mov r8, [rsp+0x20]
    mov r9, [rsp+0x28]
    syscall

    ; Get rid of the inputs from the stack
    ; Not popping, because then we can't
    ; have non-register parameters
    add rsp, 0x30

    pop r9
    pop r8
    pop r10
    pop rdx
    pop rsi
    pop rdi
%endmacro


%macro syscall5 6
  syscall6 %1, %2, %3, %4, %5, %6, 0
%endmacro

%macro syscall4 5
  syscall6 %1, %2, %3, %4, %5, 0, 0
%endmacro

%macro syscall3 4
  syscall6 %1, %2, %3, %4, 0, 0, 0
%endmacro

%macro syscall2 3
  syscall6 %1, %2, %3, 0, 0, 0, 0
%endmacro

%macro syscall1 2
  syscall6 %1, %2, 0, 0, 0, 0, 0
%endmacro
