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

menu db 10,13, "---------- Menu ----------", 10,13, "1. Addition", 10,13, "2. Subtraction", 10,13, "3. Multiplication", 10,13, "4. Signed Multiplication", 10,13, "5. Division", 10,13, "6. Signed Division", 10,13, "7. Exit", 10,13, "Enter choice : "
menulen equ $-menu

umsg db "h", 10
umsglen equ $-umsg

qmsg db "Quotient: "
qmsglen equ $-qmsg

rmsg db "Remainder: "
rmsglen equ $-rmsg

exmsg db "Exiting Program... ", 10,13
exmsglen equ $-exmsg

	un1 dq 0000000000000040h
	un2 dq 0000000000000020h
	
	sn1 dq 0xFFFFFFFFFFFFFFF8
	sn2 dq 0x0000000000000002
		
	count db 10h
	
section .bss
    result resb 16
    choice resb 01h
    rmnd resb 16
    quo resb 16
    srmnd resb 16
    squo resb 16

section .text
    global _start

_start:      
menud:	
	rw 1, menu, menulen
	rw 0, choice, 02h
	
	cmp byte[choice], 31h
	je add_case
	
	cmp byte[choice], 32h
	je sub_case
	
	cmp byte[choice], 33h
	je mul_case
	
	cmp byte[choice], 34h
	je smul_case
	
	cmp byte[choice], 35h
	je div_case
	
	cmp byte[choice], 36h
	je sdiv_case
	
	cmp byte[choice], 37h
	je ex2
		
	add_case:
		call addproc
		jmp menud
		
	sub_case:
		call subproc
		jmp menud
		
	mul_case:
		call mulproc
		jmp menud
		
	smul_case:
		call smulproc
		jmp menud
		
	div_case:
		call divproc
		jmp menud
	
	sdiv_case:
		call sdivproc
		jmp menud

ex2: 
rw 01, exmsg, exmsglen
jmp ex

addproc:
	mov rax, [un1]
	mov rbx, [un2]
	add rax, rbx
	mov [result], rax
	call h2a
	ret

subproc:
	mov rax, [un1]
	mov rbx, [un2]
	sub rax, rbx
	mov [result], rax
	call h2a
	ret

mulproc:
	mov rax, [un1]
	mov rbx, [un2]
	mul rbx
	call h2a
	ret
		
smulproc:
	mov rax, [sn1]
	mov rbx, [sn2]
	imul rbx
	call h2a
	ret

divproc: 
	xor rdx, rdx
	mov rax, qword[un1]
	mov rbx, qword[un2]
	div rbx
	mov [quo], rax
	mov [rmnd], rdx
	rw 01, qmsg, qmsglen
	mov rax, [quo]
	call h2a
	rw 01, rmsg, rmsglen
	mov rax, [rmnd]
	call h2a
	ret

sdivproc: 
	xor rdx, rdx
	mov rax, qword[sn1]
	mov rbx, qword[sn2]
	idiv rbx
	mov qword[squo], rax
	mov [srmnd], rdx
	rw 01, qmsg, qmsglen
	mov rax, [squo]
	call h2a
	rw 01, rmsg, rmsglen
	mov rax, [srmnd]
    call h2a
	ret

h2a:
    mov byte[count], 10h
    mov rbx, result
iter: 
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
    jnz iter
    rw 01, result, 16
    rw 01, umsg, umsglen
    ret
ex: exit 60                 





