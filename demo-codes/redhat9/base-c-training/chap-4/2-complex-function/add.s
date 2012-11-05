	.file	"add.c"
.globl g
	.data
	.align 4
	.type	g,@object
	.size	g,4
g:
	.long	18
	.section	.rodata
.LC0:
	.string	"g = %d \n"
	.text
.globl add
	.type	add,@function
add:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$8, %esp
	pushl	g
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	leave
	ret
.Lfe1:
	.size	add,.Lfe1-add
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
