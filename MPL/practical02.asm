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

section .data
msg db "Enter the String:",10
msglen equ $-msg

msg1 db "The lengths of string is:"
msglen1 equ $-msg1

section .bss
    string resb 20
    strlen resb 20  
           
section .text
    global _start

_start:      
    rw 01, msg, msglen
    rw 00, string, 20
    mov byte[strlen], al
    cmp byte[strlen], 09h
    jle y
    add byte[strlen], 07h  
 y: add byte[strlen], 30h
 rw 01, msg1, msglen1
 rw 01, strlen, 1  
exit 60                 

