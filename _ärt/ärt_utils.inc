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
    pop r15
    pop r14
    pop r13
    pop r12
    pop r11
    pop r10
    pop rdi
    pop rsi
    pop rbx
    pop rax
%endmacro

