section .data
EXIT_SUCCESS equ 0
SYS_exit equ 60

section .data
lst dd 2, 10, 100, 50, 5
len dd 5
min dd 99999
max dd 0

section .text
global _start

_start:
mov ecx, dword [len]
mov rsi, 0
cmpLoop:
mov eax, dword [lst+(rsi*4)]
cmp dword[min],eax
jl next
mov dword[min], eax
next:
inc rsi
loop cmpLoop

mov rsi, 0
mov ecx, dword [len]
cmpLoop2:
mov eax, dword [lst+(rsi*4)]
cmp dword[max],eax
jg next2
mov dword[max], eax
next2:
inc rsi
loop cmpLoop2

last:
mov edx, dword[min] 
mov ecx, dword[max]
mov rax, SYS_exit
mov rdi, EXIT_SUCCESS
syscall