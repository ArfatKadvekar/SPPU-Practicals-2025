%macro rw 3
    mov rax, %1        
    mov rdi, %1          
    mov rsi, %2         
    mov rdx, %3         
    syscall
%endmacro

%macro exit 0
    mov rax, 60
    mov rdi, 0
    syscall
%endmacro

section .data
    opm db "1. HEX to BCD",
    db 10, 13, "2. BCD to HEX",
    db 10, 13, "3. EXIT", 10, 13,
    db   "Enter Choice: "
    opmlen equ $-opm
   
    msg1: db "Enter 5-digit BCD number: "
    msg1len equ $-msg1

    msg2: db "Hex equivalent result is: "
    msg2len equ $-msg2

    msg3: db "Enter 4-digit HEX number: "
    msg3len equ $-msg3

    msg4: db "BCD equivalent result is: "
    msg4len equ $-msg4
   
    nl db 10


section .bss
    choice resb 1
    bcdinp resb 6
    temp resb 1
    count resb 1
    ahexinp resb 5
    hexinp resb 4



section .text
global _start
_start:

    back:

    rw 1, opm, opmlen
    rw 0, choice, 2

    cmp byte[choice], 31h
    je case1
   
    cmp byte[choice], 32h
    je case2

    exit

    b1:
        rw 1, nl, 1
        rw 1, nl, 1
        jmp back

    case1:
        rw 1, msg3, msg3len
        rw 0, ahexinp, 5
        call A2H
       
        push rax
        rw 1, msg4, msg4len
        pop rax
        call H2B
        jmp b1
   
    case2:
        rw 1, msg1, msg1len
        rw 0, bcdinp, 6
        call B2H

        rw 1, msg2, msg2len
        call H2A
        jmp b1

    exit


H2B:
    mov byte[count], 0

    mov bx, 10

    up2:
        xor rdx, rdx
        div rbx
        push rdx
        inc byte[count]
        cmp ax, 0
        jne up2

    up3:
        pop rdx
        add dl, 30H
        mov [temp], dl
        rw 1, temp, 1
        dec byte[count]
        jnz up3
    ret

B2H:
    mov rsi, bcdinp
    mov rcx, 05H

    xor rax, rax
    mov ebx, 0AH
    u1:
        xor rdx, rdx
        mul ebx
        mov dl, [rsi]
        sub dl, 30H
        add rax, rdx
        inc rsi
        loop u1
    mov rbx, rax
ret

H2A:
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

A2H:
    mov rsi, ahexinp
    mov rcx, 04H

    xor rax, rax
   
    loop2:
        shl rax, 4
        mov bl, [rsi]
        inc rsi

        cmp bl, 39h                        
        jbe down
        sub bl, 7h                        
        down:
        sub bl, 30h  
        or al, bl
        loop loop2
    ret