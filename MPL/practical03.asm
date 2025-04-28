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
arr dq 1234567891234567h, 0c325487652154687h, 0a789654574521354h, 0912357895314455h, 3545645445666556h
msg db "Largest Element: ", 10
msglen equ $-msg

count db 10h


section .bss

result resb 02
answer resb 16h

section .text
    global _start

_start:      
mov rdi, arr
mov rax, 00h    
iter:
    cmp rax, [rdi]
    jae y
   
x: mov rax, [rdi]
   
y:
    add rdi, 8
    dec byte[counter]
    jnz iter

    mov [answer], rax
    call h2a
    jmp ex

h2a:
    mov byte[count], 10h
    mov rbx, answer
iter1:
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
    jnz iter1
    rw 01, msg, msglen
    rw 01, answer, 16
    ret
ex:
exit 60
