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
    push rdx

    mov rdx, rcx  ; Keep original string pointer
    mov rcx, 0xFFFFFFFF   ; Max length of comparison

    mov rdi,rdx   ; copy string pointer
    xor rax,rax   ; search for null byte
    repne scasb   ; increment rdi until [rdi] == 0
    dec rdi       ; compensate for null byte
    sub rdi, rdx  ; string length is now in rdi
    mov rax, rdi  ; string length in rax

    pop rdx
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



; rcx: string buffer to split (will be modified)
; rdx: separator (single character)
; r8: output buffer (becomes null-terminated pointer array)
; r9: output buffer length (entries)
; returns number of parsed substrings
; returns -1 if output buffer is exhausted
;   in this case, the last output pointer contains the
;   remaining input!
global str_split
str_split:

    push rcx
    push rdi
    push rsi
    push rdx
    push r9


    mov rdi, rcx    ; incrementing string pointer (start of next string)
    mov rsi, r8     ; next output buffer space (placement of next pointer)
    xor r15, r15    ; Number of parsed substrings

    call str_length
    mov rcx, rax    ; Max search length

    movzx rax, dl   ; delimiter

    str_split_loop:

      mov [rsi], rdi    ; Output of one string
      add rsi, 8
      inc r15
      dec r9

      jnz str_split_continue
          ; Output buffer exhausted
          mov r15, -1
          jmp str_split_done

      str_split_continue:

      ; Step forward until we pass the end of a substring
      repne scasb   ; rdi++ and rcx-- until [rdi] == delimiter or rcx == 0

      ; End of input string. No extra termination needed
      test rcx, rcx
      jz str_split_done

      dec rdi       ; step back to the delimiter char
      mov [rdi], byte 0x00
      inc rdi       ; Move forward to the start of next substring

      jmp str_split_loop

    str_split_done:

    mov rax, r15    ; Return count

    pop r9
    pop rdx
    pop rsi
    pop rdi
    pop rcx
    ret

;
; rcx: single character
; returns numeric value if it's a digit
; returns -1 if it's not a digit
;
global is_digit
is_digit:
    push rcx

    mov rax, -1

    sub rcx, 0x30
    jl is_digit_no

    cmp rcx, 10
    jge is_digit_no

    mov rax, rcx

    is_digit_no:

    pop rcx
    ret