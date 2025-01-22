section .bss
num resb 2

section .text
global _start

_start:

;reading msg
mov rax, 0
mov rdi, 0
mov rsi, num
mov rdx, 2
syscall

mov al, byte[num]
x:
inc al 

y:
;writing msg
mov rax, 1
mov rdi, 1
mov rsi, num
mov rdx, 2
syscall

;exit 
mov rax, 60
mov rdi, 0
syscall
