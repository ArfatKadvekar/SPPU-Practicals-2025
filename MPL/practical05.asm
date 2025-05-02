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
counter db 05h
count db 02
pcount db 00h
ncount db 00h

pmsg db "The count of positive numbers is: "
pmsglen equ $-pmsg

nmsg db 10, "The count of negative numbers is: "
nmsglen equ $-nmsg

arr dq 23456789abcdef01h, 0d3456789abcdef01h, 0a9876543210fedc0h, 015789abcde12345h, 5abcdef123456789h

section .bss
    result resb 20
    val resb 20

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

next:
	add rdi, 8
	dec byte[counter]
	jnz iter

rw 01, pmsg, pmsglen
mov dl, byte[pcount]
mov byte[val], dl
call h2a

rw 01, nmsg, nmsglen
mov dl, byte[ncount]
mov byte[val], dl
call h2a

jmp ex

h2a:
mov al,byte[val]
xh:
cmp al,09h
jle yh
add al,07h
yh:
add al, 30h
mov byte[result],al
rw 01,result,01h
ret
ex: exit 60                 





