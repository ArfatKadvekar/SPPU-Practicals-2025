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
count db 05h

msg db "Enter the Numbers:",10,13
msglen equ $-msg

msg1 db "The Numbers are:",10,13
msglen1 equ $-msg1

section .bss
    num resb 25   
           
section .text
    global _start

_start:      
    mov rbx, num
    rw 01, msg, msglen        

x_loop:
    rw 00, rbx, 5     
    add rbx, 5     
    dec byte[count]        
    jnz x_loop
     
    rw 01, msg1, msglen1  
    mov rbx, num         
y_loop:
    rw 01, rbx, 5   
    add rbx, 5      
    dec byte[count]        
    jnz y_loop       

exit 60                 

