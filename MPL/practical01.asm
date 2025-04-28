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

msg db "Enter the Numbers:",10
msglen equ $-msg

msg1 db "The Numbers are:",10
msglen1 equ $-msg1

section .bss
    num resb 85   
           
section .text
    global _start

_start:      
    mov rbx, num
    rw 01, msg, msglen        

input_loop:
    rw 00, rbx, 17     
    add rbx, 17     
    dec byte[count]        
    jnz input_loop
     
    mov byte[count], 5 ; reset counter
    rw 01, msg1, msglen1  
    mov rbx, num 

output_loop:
    rw 01, rbx, 17   
    add rbx, 17      
    dec byte[count] 
    jnz output_loop       

exit 60                 

