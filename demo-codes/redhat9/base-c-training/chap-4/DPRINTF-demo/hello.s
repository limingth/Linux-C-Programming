	.file	"hello.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d"
	.text
.globl main
	.type	main,@function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	andl	$-16, %esp
	subl	$8, %esp
	pushl	$5
	pushl	$.LC0
	call	printf
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
.globl max
	.type	max,@function
max:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	cmpl	%edx, %eax
	jge	.L20
	movl	%edx, %eax
.L20:
	leave
	ret
.Lfe2:
	.size	max,.Lfe2-max
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
