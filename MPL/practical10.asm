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

endl db "h", 10
endlen equ $-endl

	nummsg db "Program to find Factorial of a number ",10
		db "Enter the number : ",
	nummsg_len equ $-nummsg

	resmsg db "Factorial is : "
	resmsg_len equ $-resmsg

	zerofact db " 00000001 "
	zerofactlen equ $-zerofact

section .bss
	dispbuff resb 16
	result resb 8
	num resb 1
	num1 resb 1
	numascii resb 3

section .text
    global _start

_start:   
	rw 01, nummsg, nummsg_len
	rw 00, numascii, 3
	call asciitoh
	mov [num], bl
	
	rw 01, resmsg, resmsg_len
	mov al,[num]
	cmp al, 01h
	jbe endfact
	
	mov bl, [num]
	call fact
	mov rbx, rax
	call htoa16
	jmp ex
	
endfact:
	rw 01, zerofact, zerofactlen
   
debug1:
asciitoh:

	mov bx,0
	mov byte[count],02
	mov esi,numascii
itera:
	rol bl,04
	mov al,[esi]
	cmp al,39h
	jbe xa
	sub al,07h
xa:
	sub al,30h
	add bl,al
	inc esi
	dec byte[count]
	jnz itera
	ret

htoa16: 
    mov rbx, result
    mov byte[count],10h
iterh: 
    rol rax, 4
    mov dl, al
    and dl, 0Fh
    cmp dl, 09h
    jle xh
    add dl, 07h  
    
 xh: 
    add dl, 30h
    mov [rbx], dl
    inc rbx
    dec byte[count]
    jnz iterh
    rw 01, result, 16
    rw 01, endl, endlen
ret

fact:
	cmp bl, 1
	jne do_calculation
	mov ax, 1
	ret
do_calculation:
	push rbx
	dec bl
	call fact
	pop rbx
	mul bl
	ret

ex: exit 60                 





