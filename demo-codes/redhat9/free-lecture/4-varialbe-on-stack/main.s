	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"<func> &para = 0x%x \n"
.LC1:
	.string	"<func> &i = 0x%x \n"
.LC2:
	.string	"<func> &j = 0x%x \n"
.LC3:
	.string	"<func> i = 0x%x \n"
.LC4:
	.string	"<func> j = 0x%x \n"
	.text
.globl foo
	.type	foo,@function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$8, %esp
	leal	8(%ebp), %eax
	pushl	%eax
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-8(%ebp), %eax
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-8(%ebp)
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	foo,.Lfe1-foo
	.section	.rodata
.LC5:
	.string	"<func2> &p1 = 0x%x \n"
.LC6:
	.string	"<func2> &p2 = 0x%x \n"
.LC7:
	.string	"<func2> &p3 = 0x%x \n"
.LC8:
	.string	"<func2> &p4 = 0x%x \n"
.LC9:
	.string	"<func2> &p5 = 0x%x \n"
	.text
.globl foo2
	.type	foo2,@function
foo2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$8, %esp
	leal	8(%ebp), %eax
	pushl	%eax
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	12(%ebp), %eax
	pushl	%eax
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	16(%ebp), %eax
	pushl	%eax
	pushl	$.LC7
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	20(%ebp), %eax
	pushl	%eax
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	24(%ebp), %eax
	pushl	%eax
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	foo2,.Lfe2-foo2
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
	pushl	$9
	pushl	$8
	pushl	$7
	pushl	$6
	pushl	$5
	call	foo2
	addl	$32, %esp
	subl	$12, %esp
	pushl	$5
	call	foo
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe3:
	.size	main,.Lfe3-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
