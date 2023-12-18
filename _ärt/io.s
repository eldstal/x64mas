%include "ärt_utils.inc"
%include "syscall.inc"

    EXTERN str_length
    EXTERN int_to_str


		SECTION .data

newline:
		db 0xa, 0


    SECTION .text
;
; rcx: string buffer
;
global print_str
print_str:

    enter 0, 0

    call str_length
    ; string length is in rax

    ; sys_write(fd=stdout, buf=rcx, size=rax)
    syscall3 SYS_write, 1, rcx, rax

    leave
    ret


global print_newline
print_newline:
  push rcx
  mov rcx, newline
  call print_str
  pop rcx
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


;
; Reads one whole line, replacing the \n with a NULL
; Blocking!
; rcx: file descriptor (0, probably)
; rdx: output buffer
; r8: output buffer size
; returns number of read bytes, or -1 on buffer overrun
;
global read_line
read_line:

  push rbx
  push rcx
  push rdx
  push r15

  xor rbx, rbx    ; Total read count
  mov r15, rcx

  read_line_loop:

    syscall3 SYS_read, r15, rdx, 1
    cmp rax, 1
    jl read_line_done   ; EOF or error

    cmp [rdx], byte 0xa
    je read_line_done

    inc rdx   ; prepare for next character

    ; buffer overrun test
    inc rbx   ; count the last read character
    cmp rbx, r8
    jl read_line_continue
      mov rbx, -1
      jmp read_line_done
    read_line_continue:

    ; TODO: Optimize. This label isn't needed.
    jmp read_line_loop


  read_line_done:
  mov [rdx], byte 0   ; null terminator

  mov rax, rbx    ; return value

  pop r15
  pop rdx
  pop rcx
  pop rbx
  ret
