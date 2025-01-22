section .bss
num resb 2

section .text
global _start

_start:

call read
call write

jmp exit

read:
mov rax, 0
mov rdi, 0
mov rsi, num
mov rdx, 2
syscall
ret

write:
mov rax, 01
mov rdi, 01
mov rsi, num
mov rdx, 2
syscall
ret

exit:
mov rax, 60
mov rdi, 0
syscall
