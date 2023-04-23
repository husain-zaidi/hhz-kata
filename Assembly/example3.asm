Section .data
EXIT_SUCCESS equ 0
SYS_exit equ 60
numbers dq 1, 2, 3, 3, 3, 4, 4
len dq 7
num dq 3

section .text
global _start

_start:
mov rcx, qword[len]
mov rbx, numbers
mov r12,0
mov rax, 0
mov rsi, 0

pushLoop:
push qword[rbx+r12*8]
inc r12
loop pushLoop

mov rcx, qword[len]

popLoop:
pop rax
cmp qword[num],rax
jnz unequal
inc rsi
unequal:
loop popLoop


last:
mov rax, SYS_exit
mov rdi, EXIT_SUCCESS
syscall