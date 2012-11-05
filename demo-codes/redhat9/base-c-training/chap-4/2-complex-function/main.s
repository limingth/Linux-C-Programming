	.file	"main.c"
.globl data
	.data
	.align 4
	.type	data,@object
	.size	data,4
data:
	.long	100
	.section	.rodata
.LC0:
	.string	"hello, Cruel World! \n"
.LC1:
	.string	"add = %d \n"
.LC2:
	.string	"sub = %d \n"
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
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$200
	pushl	$100
	call	sub
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.comm	val,80,32
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
