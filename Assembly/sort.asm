;Understanfing assembly language
;reverse engineering for beginners
;x86 64 assembly language programming with ubuntu

Section .data

section .text
global sort
sort:
push r12
mov ecx, dword[rsi]
mov eax, dword[rdi]
mov edx, 0

loop1:
mov r11, 0
mov r12d, dword[rdi]
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