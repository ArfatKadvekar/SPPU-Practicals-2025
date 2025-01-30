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
counter db 05h
arr db 05h, 0c3h, 0ah, 09h, 35h
 
section .text
    global _start

_start:      
	mov rdi, arr
	mov al, 00h    
iter: 
    cmp al, [rdi]
    jae x
    
    mov al, [rdi]
    
 x: 
    inc rdi
    dec byte[counter]
    
    jnz iter
   
call h2a
jmp y

h2a:

ret
y: 
exit 60                 

