	.file	"hello.c"
	.section	.rodata
.LC0:
	.string	"Hello, Cruel World! \n"
.LC1:
	.string	"argc = %d \n"
.LC2:
	.string	"argv[0] = %s \n"
.LC3:
	.string	"argv[1] = %s \n"
.LC4:
	.string	"argv[2] = %s \n"
.LC5:
	.string	"argv[3] = %s \n"
.LC6:
	.string	"argv[4] = %s \n"
.LC7:
	.string	" j = %d 0%o 0x%x \n"
.LC8:
	.string	" sizeof(int) = %d \n"
.LC9:
	.string	" sizeof(long) = %d \n"
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
	movl	$10, -4(%ebp)
	subl	$12, %esp
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	movl	12(%ebp), %eax
	pushl	(%eax)
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	movl	12(%ebp), %eax
	addl	$4, %eax
	pushl	(%eax)
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	movl	12(%ebp), %eax
	addl	$8, %eax
	pushl	(%eax)
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	movl	12(%ebp), %eax
	addl	$12, %eax
	pushl	(%eax)
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	movl	12(%ebp), %eax
	addl	$16, %eax
	pushl	(%eax)
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	pushl	-4(%ebp)
	pushl	-4(%ebp)
	pushl	-4(%ebp)
	pushl	$.LC7
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$4
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$4
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
