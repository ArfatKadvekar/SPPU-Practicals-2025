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
arr dq 1234567891234567h, 0c325487652154687h, 0a789654574521354h, 0912357895314455h, 3545645445666556h

section .bss

result resb 02

section .text
    global _start

_start:      
	mov rdi, arr
	mov al, 00h    
iter: 
    cmp al, [rdi]
    jae x
    
    mov al, [rdi]
    
 x: 
    inc rdi
    dec byte[counter]
    jnz iter
       
y: 
exit 60                 


;TODO
;need to improve this code especially that hex to ascii part


