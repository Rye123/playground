section .data
	EXIT_SUCCESS   equ  0 	; success
	SYS_EXIT       equ  60 	; terminate
	
	; Byte Declarations
	bvar1          db   17
	bvar2          db   9
	bresult        db   0

	; Word Declarations
	wvar1          dw 17000
	wvar2          dw 9000
	wresult        dw 0

	; Double Declarations
	dvar1          dd 17000000
	dvar2          dd 9000000
	dresult        dd 0

	; Quadword Declarations
	qvar1          dq 170000000
	qvar2          dq 90000000
	qresult        dq 0

section .text
global _start
_start:
	; Performs examples of addition operations
	; 1. bresult = bvar1 + bvar2
	mov   al, byte [bvar1]
	add   al, byte [bvar2]
	mov   byte [bresult], al

	; 2. wresult = wvar1 + wvar2
	mov   ax, word [wvar1]
	add   ax, word [wvar2]
	mov   word [wresult], ax

	; 3. dresult = dvar1 + dvar2
	mov   eax, dword [dvar1]
	add   eax, dword [dvar2]
	mov   dword [dresult], eax

	; 4. qresult = qvar1 + qvar2
	mov   rax, qword [qvar1]
	add   rax, qword [qvar2]
	mov   qword [qresult], rax

end:
	; exit(0)
	mov   rax, SYS_EXIT
	mov   rdi, EXIT_SUCCESS
	syscall
