%include "ärt_utils.inc"
    global str_length


;
; rcx: string buffer
;
str_length:
    enter 0, 0
    pushall

    mov rdi,rcx   ; copy string pointer
    xor rax,rax   ; search for null byte
    repne scasb   ; increment rdi until [rdi] == 0
    sub rdi, rcx  ; string length is now in rdi
    mov rax, rdi  ; string length in rax

    popall
    leave
    ret
