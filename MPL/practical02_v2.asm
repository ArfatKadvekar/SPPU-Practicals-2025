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
count db 02
msg db "Enter the String:",10
msglen equ $-msg

msg1 db "The lengths of string is:"
msglen1 equ $-msg1


section .bss
    string resb 20
    strlen resb 20  
    arr resb 02
           
section .text
    global _start

_start:      
    rw 01, msg, msglen
    rw 00, string, 20
    mov rbx, arr
    
    mov byte[count], 02h

    
iter: 
    rol al, 04h
    mov dl, al
    and dl, 0Fh
    cmp dl, 09h
    jle x
    add dl, 07h  
    
 x: 
    add dl, 30h
    mov [rbx], dl
    inc rbx
    dec byte[count]
    jnz iter
    
 rw 01, msg1, msglen1
 rw 01, arr, 02  
exit 60                 

