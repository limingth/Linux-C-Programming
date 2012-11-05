	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"x = %d \n"
.LC1:
	.string	"y = %d \n"
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
	subl	$8, %esp
	pushl	$2
	pushl	$1
	call	add
	addl	$16, %esp
	movl	%eax, -4(%ebp)
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$2
	pushl	$1
	call	sub
	addl	$16, %esp
	movl	%eax, -8(%ebp)
	subl	$8, %esp
	pushl	-8(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
