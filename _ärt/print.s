%include "ärt_utils.inc"
%include "syscall.inc"

    EXTERN str_length
    EXTERN int_to_str

;
; rcx: string buffer
;
global print_str
print_str:

    enter 0, 0

    call str_length
    ; string length is in rax

    ; sys_write(fd=stdout, buf=rcx, size=rax)
    syscall3 SYS_write, 0, rcx, rax

    leave
    ret


;
; rcx: integer
; rdx: base ([1, 16])
;
global print_int
print_int:
		enter 256, 0

		push rcx
		push r8
		push rdx

		mov r8, rdx				; base
		mov rdx, rcx			; integer
		mov rcx, rsp			; buffer
		call int_to_str

		mov rcx, rsp			; buffer
		call print_str

		pop rdx
		pop r8
		pop rcx

		leave
		ret

