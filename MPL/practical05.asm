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
pcount db 00h
ncount db 00h

pmsg db "The count of positive numbers is:",10
pmsglen equ $-pmsg

nmsg db "The count of negative numbers is:",10
nmsglen equ $-nmsg

arr dq 23456789abcdef01h, 0d3456789abcdef01h, 0a9876543210fedc0h, 015789abcde12345h, 5abcdef123456789h


section .text
    global _start

_start:      
	mov rdi, arr
iter: 
	mov rbx, 8000000000000000h
	and [rdi], rbx
	jnz x
	mov al, byte[pcount]
	inc al
	mov byte[pcount], al
	jmp next
x: 
	mov dl, byte[ncount]
	inc dl
	mov byte[ncount], dl

next: 	add rdi, 8
	dec byte[counter]
	jnz iter
       
debug:
 rw 01, pmsg, pmsglen
 rw 01, pcount, 02h
 rw 01, nmsg, nmsglen
 rw 01, ncount, 02h

h2a:
    mov byte[strlen], al
    cmp byte[strlen], 09h
    jle add30
    add byte[strlen], 07h  
 add30: add byte[strlen], 30h
exit 60                 





