//
//  functions.s
//  Euler
//
//  Created by Michael Nolan on 1/10/16.
//  Copyright © 2016 Michael Nolan. All rights reserved.
//rdi, rsi, rdx, rcx, r8, r9
.intel_syntax noprefix
.text
.macro f_begin //macros for function beginning and ending
	push rbp
	mov rbp,rsp
.endm
.macro f_end
	pop rbp
	ret
.endm
.macro symb name:req
	.global \name
	\name:
	f_begin
.endm
symb _fibArray
	push rbx
	push rdi
	shl rax,3
	call _malloc

	pop rdi
	xchg rax,rdi
	mov rsi,rdi
	mov rcx,rax
	mov rbx,1
	mov rax,0
1:
	add rax,rbx
	xchg rax,rbx
	mov [rdi],rbx
	add rdi,8
	sub rcx,1
	jne 1b


	mov rax,rsi
	pop rbx
	f_end
symb _sumArray

	mov rcx,rdi
	xor r8,r8
1:
	lodsq
	cmp rax,4000000
	jg 2f
	test rax,1
	jne 3f
	add r8,rax
3:	sub rcx,1
	jne 1b

2:
	mov rax,r8
	f_end

