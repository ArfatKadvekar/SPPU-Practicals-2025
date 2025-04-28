%macro rw 3
mov rax, %1
mov rdi, %1
mov rsi, %2
mov rdx, %3
syscall
%endmacro

%macro exit 1
mov rax, %1
mov rdi, 0
syscall
%endmacro

section .bss
num resb 2

section .text
global _start

_start:

rw 00, num, 2
rw 01, num, 2

exit 60
;exit 
;mov rax, 60
;mov rdi, 0
;syscall
