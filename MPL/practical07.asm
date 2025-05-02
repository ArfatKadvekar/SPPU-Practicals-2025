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
count db 10h
count2 db 20h
endl db "h", 10
endlen equ $-endl

pmsg db "The processor is in protected mode",10
pmsglen equ $-pmsg

tr db "TR: " 
trlen equ $-tr 

ldt db "LDT: " 
ldtlen equ $-ldt

msw db "MSW: " 
mswlen equ $-msw

idtr db "IDTR: " 
idtrlen equ $-idtr

gdtr db "GDTR: " 
gdtrlen equ $-gdtr


section .bss
    result resb 20
    val resb 20
    trv resb 4
    ldtv resb 4
    gdtv resb 6
    idtv resb 6
    mswv resb 4
    v1 resb 4
    v2 resb 2

section .text
    global _start

_start:   

smsw rax 
bt rax, 0
jc pm

pm:
   rw 01, pmsg, pmsglen
   rw 01, tr, trlen
   str [trv]
   mov rax, [trv]
   call htoa16
   
   rw 01, ldt, ldtlen
   sldt [ldtv]
   mov rax, [ldtv]
   call htoa16
   
   rw 01, msw, mswlen
   smsw [mswv]
   mov rax, [mswv]
   call htoa16
   
   rw 01, gdtr, gdtrlen
   sgdt [gdtv]
   mov eax, dword[gdtv]
   mov dword[v1], eax
   call htoa32
   
   mov ax, word[gdtv+4]
   mov word[v2], ax
   call htoa16
   
   rw 01, idtr, idtrlen
   sidt [idtv]
   mov eax, dword[idtv]
   mov dword[v1], eax
   call htoa32
   
   mov ax, word[idtv+4]
   mov word[v2], ax
   call htoa16
   jmp ex
   
 
htoa16: 
    mov rbx, result
    mov byte[count], 10h
iterh: 
    rol ax, 04h
    mov dx, ax
    and dx, 0Fh
    cmp dl, 09h
    jle xh
    add dl, 07h  
    
 xh: 
    add dl, 30h
    mov [rbx], dl
    inc rbx
    dec byte[count]
    jnz iterh
    rw 01, result, 8
    rw 01, endl, endlen
ret


htoa32: 
    mov rbx, result
    mov byte[count2], 20h
iterh2: 
    rol eax, 04h
    mov edx, eax
    and edx, 0Fh
    cmp dl, 09h
    jle xh2
    add dl, 07h  
    
 xh2: 
    add dl, 30h
    mov [rbx], dl
    inc rbx
    dec byte[count2]
    jnz iterh2
    rw 01, result, 8
    rw 01, endl, endlen
ret

ex: exit 60                 





