	.file	"main.c"
	.text
.globl add
	.type	add,@function
add:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	leave
	ret
.Lfe1:
	.size	add,.Lfe1-add
.globl sub
	.type	sub,@function
sub:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	subl	%edx, %eax
	leave
	ret
.Lfe2:
	.size	sub,.Lfe2-sub
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
.Lfe3:
	.size	main,.Lfe3-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
