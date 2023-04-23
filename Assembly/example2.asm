;Understanding assembly language
;reverse engineering for beginners
;x86 64 assembly language programming with ubuntu

Section .data
EXIT_SUCCESS equ 0
SYS_exit equ 60
numbers dd 124, 123, 121, 125, 122
len dd 5
temp dd 0
len2 dd 5

section .text
global _start
_start:

mov ecx, dword[len]
mov eax, numbers


loop1:
mov rdi, 0
mov rsi, 4
loop2:
mov eax, dword[numbers+(rdi*4)] 
mov ebx, dword[numbers+((rdi*4)+4)]
cmp eax,ebx
jl next
;swap
mov dword[temp],eax
mov eax, ebx
mov ebx, dword[temp] 
mov dword[numbers+(rdi*4)], eax
mov dword[numbers+(rdi*4)+4], ebx
next:
inc rdi
dec rsi
jnz loop2
loop loop1

last:
mov rax, SYS_exit
mov rdi, EXIT_SUCCESS
syscall
