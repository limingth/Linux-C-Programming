	.file	"main.c"
.globl liming
	.data
	.align 32
	.type	liming,@object
	.size	liming,40
liming:
	.long	100
	.zero	36
.globl zhang
	.align 4
	.type	zhang,@object
	.size	zhang,4
zhang:
	.long	100
.globl si
	.section	.rodata
	.align 4
	.type	si,@object
	.size	si,4
si:
	.long	200
.LC0:
	.string	"hello, world \n"
.LC1:
	.string	"add(100, 200) = %d \n"
.LC2:
	.string	"sub(100, 200) = %d \n"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$200
	pushl	$100
	call	add
	addl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$200
	pushl	$100
	call	sub
	addl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$200
	pushl	$100
	call	sub
	addl	$8, %esp
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.comm	zhang2,4,4
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
