;Understanfing assembly language
;reverse engineering for beginners
;x86 64 assembly language programming with ubuntu

section .data
LF equ 10
NULL equ 0
TRUE equ 1
FALSE equ 0

EXIT_SUCCESS equ 0
SYS_exit equ 60


lst1 dd 1, -2, 3, -4, 5
len dd 5


externs sort
section .text
mov rdi, lst1
mov esi, word[len1]
call sort

mov rax, SYS_exit
mov rdi, EXIT_SUCCESS
syscall

global sort
sort:
push r12
mov ecx, dword[rsi]
mov eax, dword[rdi]
mov edx, 0

loop1:
mov r11, 0
mov r12d, dword[rsi]
dec r12d
loop2:
mov eax, dword[rdi+(r11*4)] 
mov ebx, dword[rdi+((r11*4)+4)]
cmp eax,ebx
jl next
;swap
mov edx,eax
mov eax, ebx
mov ebx, edx 
mov dword[rdi+(r11*4)], eax
mov dword[rdi+(r11*4)+4], ebx
next:
inc r11
dec r12d
jnz loop2
loop loop1
pop r12
ret