	.file	"hello.cpp"
.globl a
	.bss
	.align 4
	.type	a,@object
	.size	a,4
a:
	.zero	4
.globl b
	.align 4
	.type	b,@object
	.size	b,4
b:
	.zero	4
.globl c
	.align 4
	.type	c,@object
	.size	c,4
c:
	.zero	4
.globl str
	.data
	.align 32
	.type	str,@object
	.size	str,32
str:
	.string	"aabbccdd"
	.zero	23
.globl myint
	.align 4
	.type	myint,@object
	.size	myint,4
myint:
	.long	17
	.section	.rodata
.LC0:
	.string	"no welcome msg! \n"
.LC1:
	.string	"argc is ok: %3d \n"
.LC2:
	.string	"argc is ok: %d \n"
.LC3:
	.string	"argc is error \n"
	.text
	.align 2
.globl main
	.type	main,@function
main:
.LFB2:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$8, %esp
.LCFI2:
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	subl	$12, %esp
	pushl	$.LC0
.LCFI3:
	call	printf
	addl	$16, %esp
	cmpl	$0, 8(%ebp)
	jle	.L2
	cmpl	$4, 8(%ebp)
	jg	.L2
	subl	$8, %esp
	pushl	$1
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$1
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	jmp	.L3
.L2:
	subl	$12, %esp
	pushl	$.LC3
	call	printf
	addl	$16, %esp
.L3:
	movl	$16, %eax
	leave
	ret
.LFE2:
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
