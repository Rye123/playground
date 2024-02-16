	section .data
	err db 0xa, "ERROR", 0xa
	err_len dd 7

	section .bss
	mem resb 256
	buf resb 256		; Buffer for input
	
	
	section .text
	global _start

;;; get_input: Takes input from stdin, storing in buf
get_input:
	;;    read(unsigned int fd, char *buf, size_t count)
	push ebp
	mov ebp, esp
	mov eax, 3
	mov ebx, 0 		; stdin
	lea ecx, [buf]
	mov edx, 254
	int 0x80

	mov byte [buf+255], 0
	pop ebp
	ret

	
;;; get_next_index: Scans arg1 backward for arg2. Returns the relative index of arg2, or -1 in EAX
;;;   Arguments: arg1=ptr to array, arg2=expected character
get_next_index:
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	push edx
	mov eax, -1 		; Return value
	mov ebx, [ebp+8] 	; current address (arg1 + iterator)
	xor ecx, ecx		; current character
	xor edx, edx 		; expected character
	mov dl, [ebp+0xc]

get_next_index_loop:
	mov cl, [ebx]

	cmp cl, dl
	je get_next_index_found
	cmp cl, 0
	je get_next_index_exit

	add ebx, 1
	jmp get_next_index_loop

get_next_index_found:
	;; Get relative index
	mov eax, ebx
	sub eax, [ebp+8]
	
get_next_index_exit:
	pop edx
	pop ecx
	pop ebx
	pop ebp
	ret

;;; get_prev_index: Scans arg1 backward for arg2. Returns the relative index of arg2, or -1 in EAX
;;;   Arguments: arg1=ptr to array, arg2=expected character
get_prev_index:
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	push edx
	mov eax, -1 		; Return value
	mov ebx, [ebp+8] 	; current address (arg1 + iterator)
	xor ecx, ecx		; current character
	xor edx, edx 		; expected character
	mov dl, [ebp+0xc]

get_prev_index_loop:
	mov cl, [ebx]

	cmp cl, dl
	je get_prev_index_found
	cmp cl, 0
	je get_prev_index_exit

	sub ebx, 1

	;; ensure not less than zero
	cmp ebx, -1
	je get_prev_index_exit
	jmp get_prev_index_loop

get_prev_index_found:
	;; Get relative index
	mov eax, ebx
	sub eax, [ebp+8]
	
get_prev_index_exit:
	pop edx
	pop ecx
	pop ebx
	pop ebp
	ret

interpret:
	;; Prologue
	push ebp
	mov ebp, esp
	sub esp, 0xc

	;; Initialise vars
	mov dword [ebp-4], 0x0 	; code ptr
	mov dword [ebp-8], mem 	; memory ptr

interpret_parse:
	;; Get current character into EAX
	mov dword edi, [ebp-4]
	xor eax, eax
	mov byte al, [buf+edi]

	;; If character is valid brainfuck character
	cmp al, 0x3e		; '>'
	je interpret_parse_ptr_mov_r
	cmp al, 0x3c		; '<'
	je interpret_parse_ptr_mov_l
	cmp al, 0x2b		; '+'
	je interpret_parse_mem_inc
	cmp al, 0x2d		; '-'
	je interpret_parse_mem_dec
	cmp al, 0x2e		; '.'
	je interpret_parse_mem_out
	cmp al, 0x2c		; ','
	je interpret_parse_mem_in
	cmp al, 0x5b		; '['
	je interpret_parse_jfez
	cmp al, 0x5d		; ']'
	je interpret_parse_jbnz
	cmp al, 0x00		; '\0': EXIT
	je interpret_exit

interpret_parse_loop:
	add dword [ebp-4], 1
	jmp interpret_parse

interpret_parse_ptr_mov_r:	; '>': Pointer Move Right
	add dword [ebp-8], 1
	jmp interpret_parse_loop
interpret_parse_ptr_mov_l:	; '<': Pointer Move Left
	sub dword [ebp-8], 1
	jmp interpret_parse_loop
interpret_parse_mem_inc:	; '+': Memory Increment at cell
	mov edi, [ebp-8]
	add dword [edi], 1
	jmp interpret_parse_loop
interpret_parse_mem_dec:	; '-': Memory Decrement at cell
	mov edi, [ebp-8]
	sub dword [edi], 1
	jmp interpret_parse_loop
interpret_parse_mem_out:	; '.': Output character at cell
	;; write(unsigned int fd, const char *buf, size_t count)
	mov eax, 4		; write
	mov ebx, 1		; stdout
	mov ecx, [ebp-8]	; arg1
	mov edx, 1
	int 0x80
	
	jmp interpret_parse_loop
interpret_parse_mem_in:		; ',': Input character at cell
	;; read(unsigned int fd, const char *buf, size_t count)
	mov eax, 3		; read
	mov ebx, 0		; stdin
	mov ecx, [ebp-8]	; arg1
	mov edx, 1
	int 0x80
	
	jmp interpret_parse_loop
interpret_parse_jfez:		; '[': Jump forward if cell == 0, to next ']'
	mov edi, [ebp-8]

	cmp dword [edi], 0
	;; if mem[mem_ptr] != 0
	jne interpret_parse_loop
	;; else: jump to next ']'

	;; get_next_index(buf + code_ptr, ']')
	lea edi, buf
	add edi, [ebp-4]
	push 0x5d 		; ']'
	push dword edi
	call get_next_index
	add esp, 0x8

	;; check if cannot find next index
	cmp dword eax, -1
	je _error

	add dword [ebp-4], eax
	jmp interpret_parse_loop
interpret_parse_jbnz:		; ']': Jump backward if cell != 0, to prev '['
	mov edi, [ebp-8]

	cmp dword [edi], 0
	;; if mem[mem_ptr] == 0
	je interpret_parse_loop
	;; else: jump to next ']'
	
	;; get_prev_index(buf + code_ptr, '[')
	lea edi, buf
	add edi, [ebp-4]
	push 0x5b 		; '['
	push dword edi
	call get_prev_index
	add esp, 0x8

	;; check if cannot find next index
	cmp dword eax, -1
	je _error

	sub dword [ebp-4], eax
	jmp interpret_parse_loop

interpret_exit:
	add esp, 0xc
	pop ebp
	ret

_error:
	;; write(unsigned int fd, const char *buf, size_t count)
	mov eax, 4
	mov ebx, 2		; stderr
	lea ecx, [err]
	mov dword edx, [err_len]
	int 0x80
	
	mov eax, 1
	xor ebx, ebx
	mov ebx, 1
	int 0x80

;;; start
_start:
	;; Prologue
	push ebp
	mov ebp, esp
	xor edi, edi

init_mem:
	mov dword [mem+edi], 0x00
	inc edi
	cmp edi, 254
	jne init_mem

interpret_code:	
	;; Store source code from stdin into buf
	call get_input
	call interpret


	;; Epilogue
	pop ebp
	
	
	;; write(unsigned int fd, const char *buf, size_t count)
	;; mov eax, 4
	;; mov ebx, 2		; stderr
	;; mov ecx, mem
	;; mov dword edx, 256
	;; int 0x80
	
	;; Exit
	mov eax, 1
	xor ebx, ebx
	int 0x80
