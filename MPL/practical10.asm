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
	fname db "demo.txt", 0
	
section .bss
  global buffer 
  buffer resb 100
  fd resb 64
  
section .text
    global _start

_start: 

open: 
	mov rax, 02
	mov rdi, fname
	mov rsi, 02h
	mov rdx, 0777h
	syscall
	
	mov fd, rax
	
read:
	mov rax, 00
	mov rdi, [fd]
	mov rsi, buffer
	mov rdx, 100
	syscall

close:
	mov rax, 03
	mov rdi, [fd]
	syscall

	rw 01, buffer 
ex: exit 60
