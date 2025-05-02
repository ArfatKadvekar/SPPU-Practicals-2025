%macro rw 3
mov  rax , %1  ; sys_write
mov  rdi , %1  ; stdout - file descriptor
mov  rsi , %2  ; address of string to print
mov  rdx , %3  ; no. of bytes to print
syscall
%endmacro

%macro exit  0
mov  rax , 60   ; sys_exit
mov  rdx , 00   
syscall 
%endmacro

section .data
msg1  db  "Enter string: " , 0xA
len1  equ  $-msg1


section .bss
string resb  100   ; Allocate max. 100 bytes for the string
length resb  2     ; Length is printed in two bytes


section .text
global _start
_start:

rw 01, msg1   , len1
rw 00,string , 100

; length of input string is stored in al

dec  al                ; Decrement al to compensate for trailing null character
mov  bl  , al          ; Copy contents of al to bl
mov  rax , length      ; mov 'length' base address to rsi
mov  rcx , 02h         ; reset counter to 0x02

hextoascii:
rol  bl  , 04          ; rotate left 4 times (i.e. swap nibbles)
mov  dl  , bl          ; copy byte from bl to dl
and  dl  , 0Fh         ; perform AND to 0x0F ( 0000 1111 in binary )
cmp  dl  , 09h         ; compare with 09h
jbe  copydigit         ; Jump to label 'next1' if result of cmp was below or equal
add  dl  , 07h         ; Add 07h if greater than 09h

copydigit:
add  dl  , 30h         ; Add 30h always
mov  [rax]  ,  dl      ; copy byte from dl to location specified by rsi
inc  rax               ; increment rsi index
dec  rcx               ; decrement counter
jnz  hextoascii        ; Go to 'up' hextoascii if rcx is not zero

rw 01, length , 02      ; Print the 'ans' array upto 2 bytes

exit