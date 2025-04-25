section .data
    msg1 db "Your Number is: "
    msg1len equ $-msg1

    msg2 db "Factorial is: "
    msg2len equ $-msg2

msg3 db "Factorial is 01"
msg3len equ $-msg3
nl db 10

count db 0
       
section .bss
  num resb 1
temp resb 1
res resb 8


%macro rw 3
    mov rax, %1
    mov rdi, %1
    mov rsi, %2
    mov rdx, %3
    syscall
%endmacro


section .text
global _start
_start:
    pop rbx  ; Discrading argument count
    pop rbx  ; Discarding program name
    pop rbx  ; Storing number in rbx

; storing in num variable
    mov al, byte[rbx]
    mov [num], al

; Printing number
    rw 1, msg1, msg1len
rw 1, num, 1

; Handling 0 and 1
cmp byte[num], 31h
je one
cmp byte[num], 30h
je one


; Converting to hex
mov bl, byte[num]
call A2H

xor rax, rax
xor rdx, rdx

rw 1, nl, 1

mov al, byte[num]

; Preparing stack.
iter:
push rax
inc byte[count]
dec rax
cmp rax, 1
jne iter

push rax
xor rax, rax

pop rax

ft:
pop rdx
mul rdx
dec byte[count]
jnz ft

mov qword[res], rax

rw 1, msg2, msg2len
call H2A

jmp exit

one:
rw 1, nl, 1
rw 1, msg3, msg3len
jmp exit

; Procs

A2H:                              
cmp bl, 39h                        
jbe down
sub bl, 7h                        
down:
sub bl, 30h                        
mov [num], bl                      
ret

H2A:
mov rbx, qword[res]
mov byte[count], 8
loop1:
rol ebx, 4
mov al, bl
and al, 0FH
cmp al, 09H
jg a1
add al, 30H
jmp a2

a1: add al, 37H

a2: mov [temp], al
rw 1, temp, 1
dec byte[count]
jnz loop1

ret

exit:
mov rax, 60
mov rdi, 0
syscall

