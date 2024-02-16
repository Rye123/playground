	section .bss
	src_sz resb 4
	mem resb 255		; Memory for brainfuck program
	buf resb 255		; Buffer for input
	src resb 255		; Buffer for source code
	
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
	mov edx, 255
	int 0x80
	pop ebp
	ret

;;; parse_src: Parses only valid brainfuck characters from buffer into src, storing the length into src_sz
parse_src:	
	;; Prologue
	push ebp
	mov ebp, esp
	
	;; Initialise variables
	xor edi, edi
	xor ebx, ebx

parse_src_process:	
	;; Process input into src
	xor eax, eax
	mov byte al, [buf+edi] 	; current character

	;; If current character is a valid brainfuck character
	cmp al, 0x3e		; '>'
	je parse_src_process_save
	cmp al, 0x3c		; '<'
	je parse_src_process_save
	cmp al, 0x2b		; '+'
	je parse_src_process_save
	cmp al, 0x2d		; '-'
	je parse_src_process_save
	cmp al, 0x2e		; '.'
	je parse_src_process_save
	cmp al, 0x2c		; ','
	je parse_src_process_save
	cmp al, 0x5b		; '['
	je parse_src_process_save
	cmp al, 0x5d		; ']'
	je parse_src_process_save
	cmp al, 0x00
	je parse_src_exit
	;; Else, loop
	jmp parse_src_process_loop

parse_src_process_save:	
	;; Save to src
	mov byte [src+ebx], al 	; save to src
	add ebx, 1

parse_src_process_loop:	
	;; Increment i and loop
	add edi, 1
	jmp parse_src_process
	
parse_src_exit:
	;; Set size of src
	mov dword [src_sz], ebx
	
	;; Epilogue
	pop ebp
	ret

;;; start
_start:
	call get_input
	call parse_src

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
