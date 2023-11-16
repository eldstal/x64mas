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
    ; string length is in rax

    ; sys_write(fd=stdout, buf=rcx, size=rax)
    syscall3 1, 0, rcx, rax

    popall
    leave
    ret
