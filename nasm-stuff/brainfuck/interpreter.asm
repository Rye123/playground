	section .bss
	buf resb 255
	src resb 255
	src_sz resb 4
	mem resb 100

	section .text
	global _start

get_input:
	;; Prologue
	push ebp
	mov ebp, esp
	sub esp, 0x4 		; i

	;; 1. Read input from stdin
	;;    read(unsigned int fd, char *buf, size_t count)
	mov eax, 3
	mov ebx, 0 		; stdin
	lea ecx, [buf]
	mov edx, 255
	int 0x80

	;; i = 0
	mov dword [ebp-4], 0x0
	mov dword [src_sz], 0x0

get_input_process:
	;; 2. Process input into src
	mov dword edi, [ebp-4]
	xor eax, eax
	mov byte al, [buf+edi] 	; current character

	;; If current character is a valid brainfuck character
	cmp al, 0x3e		; '>'
	je get_input_save_to_src
	cmp al, 0x3c		; '<'
	je get_input_save_to_src
	cmp al, 0x2b		; '+'
	je get_input_save_to_src
	cmp al, 0x2d		; '-'
	je get_input_save_to_src
	cmp al, 0x2e		; '.'
	je get_input_save_to_src
	cmp al, 0x2c		; ','
	je get_input_save_to_src
	cmp al, 0x5b		; '['
	je get_input_save_to_src
	cmp al, 0x5d		; ']'
	je get_input_save_to_src
	;; Else, skip
	jmp get_input_process_loop

get_input_save_to_src:	
	;;    Save to src
	mov byte [src+edi], al 	; save to src

get_input_process_loop:	
	;;    Check if current char == '\0'
	test al, al 		; ZF = 1 if cur char is \0
	jz get_input_exit
	
	;; 2.2. Increment i and loop
	add edi, 1
	mov dword [ebp-4], edi
	jmp get_input_process
	
get_input_exit:
	;; Set size of src
	mov dword edi, [ebp-4]
	mov dword [src_sz], edi
	
	;; Epilogue
	add esp, 0x4 		; dealloc space for i
	pop ebp
	ret

	
_start:
	call get_input

	;; write(unsigned int fd, const char *buf, size_t count)
	mov eax, 4
	mov ebx, 1		; stdout
	lea ecx, [src]
	mov dword edx, [src_sz]
	int 0x80

	;; Exit
	mov eax, 1
	xor ebx, ebx
	int 0x80
