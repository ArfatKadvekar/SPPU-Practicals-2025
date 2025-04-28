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
arr dq 30h,40h,60h,20h,70h
dst dq 0000000000000000h,0000000000000000h,0000000000000000h,0000000000000000h,0000000000000000h

count db 10h
cnt db 05h

umsg db "h"
umsglen equ $-umsg

tab db " : "
tablen equ $-tab

endl db " ", 10
endlen equ $-endl

smsg db "-----------------Source -----------------------", 10
smsglen equ $-smsg

dmsg db "--------------------Destination ----------------", 10
dmsglen equ $-dmsg
section .bss
    result resb 16
    var resb 16
section .text
    global _start

_start: 

	rw 01, smsg, smsglen
source:
	mov byte[cnt], 05h
	mov rsi, arr
iter:	mov qword[var], rsi
	push rsi
	call h2a
	rw 01, tab, tablen
	pop rsi

	mov rax, [rsi]
	mov qword[var], rax
	push rsi
	call h2a
	rw 01, endl, endlen
	pop rsi
	
	add rsi, 08h
	dec byte[cnt]
	jnz iter

	mov rsi, arr + (4*8)
	mov rdi, arr + (7*8)
	mov rcx, 05h
	std
	rep movsq
	
	rw 01, dmsg, dmsglen
	
dest:
	mov byte[cnt], 05h
	mov rsi, dst - 10h
iterd:	mov qword[var], rsi
	push rsi
	call h2a
	rw 01, tab, tablen
	pop rsi

	mov rax, [rsi]
	mov qword[var], rax
	push rsi
	call h2a
	rw 01, endl, endlen
	pop rsi
	
	add rsi, 08h
	dec byte[cnt]
	jnz iterd
jmp ex

h2a:
    mov byte[count], 10h
    mov rax, qword[var]
    mov rbx, result
iteri: 
    rol rax, 04h
    mov dl, al
    and dl, 0Fh
    cmp dl, 09h
    jle xi
    add dl, 07h  
    
 xi: 
    add dl, 30h
    mov [rbx], dl
    inc rbx
    dec byte[count]
    jnz iteri
    rw 01, result, 16
    rw 01, umsg, umsglen
    
    
    ret

ex: exit 60
