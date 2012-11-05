	.file	"main.c"
.globl globle_var
	.data
	.align 4
	.type	globle_var,@object
	.size	globle_var,4
globle_var:
	.long	4660
.globl const_num
	.section	.rodata
	.align 4
	.type	const_num,@object
	.size	const_num,4
const_num:
	.long	39321
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
	subl	$4, %esp
	pushl	$3
	pushl	$2
	pushl	$1
	call	max
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
