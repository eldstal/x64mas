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
