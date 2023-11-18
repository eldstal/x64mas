%include "ärt_utils.inc"


		SECTION .data

digits:
		db "0123456789ABCDEF", 0




		SECTION .text

;
; rcx: string buffer
;
global str_length
str_length:
    enter 0, 0

    push rdi
		push rcx

    mov rdi,rcx   ; copy string pointer
    xor rax,rax   ; search for null byte
    repne scasb   ; increment rdi until [rdi] == 0
    sub rdi, rcx  ; string length is now in rdi
    mov rax, rdi  ; string length in rax

		pop rcx
		pop rdi
    leave
    ret



; rcx: string buffer of suitable size
; rdx: unsigned integer
; r8: base (>0, <= 16)
;
; Returns the string length (excluding null terminator)
global int_to_str
int_to_str:
		enter 0, 0

		push r9
		push rdx
		push rcx
		push r8

		mov rax, rdx
		xor r9, r9		; Character count

		; Divide the input integer into individual digits 0...base
		int_to_str_digits:

				; rax = rax / r8
				; rdx = rax % r8
				xor rdx, rdx
				div r8

				push rdx
				inc r9

				test rax, rax
		jnz int_to_str_digits

		; Return value
		mov rax, r9
		lea r8, [digits]

		int_to_str_text:
				pop rdx
				movzx rdx, byte [r8+rdx]			; Character for this digit

				mov [rcx], dl
				inc rcx

				dec r9
		jnz int_to_str_text

		; Null terminator
		mov [rcx], byte 0


		pop r8
		pop rcx
		pop rdx
		pop r9

		leave
		ret
