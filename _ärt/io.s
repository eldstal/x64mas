%include "ärt_utils.inc"
%include "syscall.inc"

    EXTERN str_length
    EXTERN int_to_str


		SECTION .data

newline:
		db 0xa, 0


%define STDIN_BUF_SIZE 4096

stdin_buf:
    times STDIN_BUF_SIZE db 0

stdin_buf_length:
    dq 0    ; total number of bytes placed in stdin_buf
            ; If < STDIN_BUF_SIZE, it's EOF

stdin_buf_idx:
    dq 0    ; inside of std_buf, next byte to read

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
; rcx: file descriptor (ignored)
; rdx: output buffer
; r8: output buffer size
; returns number of read bytes, or -1 on buffer overrun
;
global read_line
read_line:

  push rbx
  push rcx
  push rdx
  push r14
  push r15

  xor rbx, rbx    ; Total read count
  ;mov r15, rcx

  read_line_loop:


    mov r15, [stdin_buf_idx]
    mov r14, [stdin_buf_length]
    cmp r15, r14
    jne read_line_buf_filled  ; No need to fill the buffer just yet

    read_line_refill:
      xor rax,rax
      mov [stdin_buf_idx], rax
      syscall3 SYS_read, 0, stdin_buf, STDIN_BUF_SIZE
      mov [stdin_buf_length], rax
      cmp rax, 1
      jl read_line_done   ; EOF or error


    read_line_buf_filled:

    ; Read one byte from the buffer to [rdx]
    mov rdi, stdin_buf
    add rdi, [stdin_buf_idx]
    mov rdi, [rdi]
    mov [rdx], rdi

    inc qword [stdin_buf_idx]


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
  pop r14
  pop rdx
  pop rcx
  pop rbx
  ret
