%macro rw 3
    mov rax, %1        
    mov rdi, 1          
    mov rsi, %2         
    mov rdx, %3         
    syscall
%endmacro

%macro exit 1
    mov rax, %1         
    mov rdi, 0          
    syscall
%endmacro

section .data

menu db "========== Menu ==========",10,13, "1. Addition", 10, 13,"2. Substraction", 10, 13,"3. Multiplication", 10, 13,"4. Unsigned Multiplication", 10, 13,"5. Division", 10, 13,"6. Unsigned Division", 10, 13,"7. Exit", 10, 13,"Enter Choice: "
menulen equ $-menu

choice db 01h

sn1 dq 23456789abcdef01h
sn2 dq 10h

section .text
    global _start

_start:      
	rw 01, menu, menulen
	rw 00, choice, 01h
	cmp byte[choice], 31h
	jne next1
	jmp debug
next1: 
	mov al, byte[sn1]
	add al, byte[sn2]
debug:



exit 60                 





