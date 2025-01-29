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
count db 10h

section .bss
    arr resb 16
           
section .text
    global _start

_start:      
    mov rax, 0fffffffffffffffh
    mov rbx, arr
    mov byte[count], 10h

    
iter: 
    rol rax, 04h
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
rw 01, arr, 16
exit 60                 

