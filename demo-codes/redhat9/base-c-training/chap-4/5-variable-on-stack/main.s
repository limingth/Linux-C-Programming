	.file	"main.c"
.globl addr
	.data
	.align 4
	.type	addr,@object
	.size	addr,4
addr:
	.long	0
	.local	j.0
	.comm	j.0,4,4
	.section	.rodata
.LC0:
	.string	"<func> &para = 0x%x \n"
.LC1:
	.string	"<func> para = 0x%x \n"
.LC2:
	.string	"<func> &i = 0x%x \n"
.LC3:
	.string	"<func> i = 0x%x \n"
.LC4:
	.string	"<func> &j = 0x%x \n"
.LC5:
	.string	"<func> j = 0x%x \n"
.LC6:
	.string	"<func> --- out --- \n"
	.text
.globl test
	.type	test,@function
test:
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
	pushl	8(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
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
	pushl	$j.0
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	j.0
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	leal	-4(%ebp), %eax
	movl	%eax, addr
	subl	$12, %esp
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$2
	call	sleep
	addl	$16, %esp
	subl	$12, %esp
	pushl	$5
	call	test
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	test,.Lfe1-test
	.local	jj.1
	.comm	jj.1,4,4
	.section	.rodata
.LC7:
	.string	"<func2> &para = 0x%x \n"
.LC8:
	.string	"<func2> para = 0x%x \n"
.LC9:
	.string	"<func2> &p2 = 0x%x \n"
.LC10:
	.string	"<func2> &p3 = 0x%x \n"
.LC11:
	.string	"<func2> &p4 = 0x%x \n"
.LC12:
	.string	"<func2> &p5 = 0x%x \n"
.LC13:
	.string	"<func2> p2 = 0x%x \n"
.LC14:
	.string	"<func2> p3 = 0x%x \n"
.LC15:
	.string	"<func2> p4 = 0x%x \n"
.LC16:
	.string	"<func2> p5 = 0x%x \n"
.LC17:
	.string	"<func2> &k1 = 0x%x \n"
.LC18:
	.string	"<func2> k1 = 0x%x \n"
.LC19:
	.string	"<func2> &k2 = 0x%x \n"
.LC20:
	.string	"<func2> k2 = 0x%x \n"
.LC21:
	.string	"<func2> &jj = 0x%x \n"
.LC22:
	.string	"<func2> jj = 0x%x \n"
.LC23:
	.string	"<func2> --- out --- \n"
	.text
.globl test2
	.type	test2,@function
test2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	subl	$8, %esp
	leal	8(%ebp), %eax
	pushl	%eax
	pushl	$.LC7
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	12(%ebp), %eax
	pushl	%eax
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	16(%ebp), %eax
	pushl	%eax
	pushl	$.LC10
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	20(%ebp), %eax
	pushl	%eax
	pushl	$.LC11
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	24(%ebp), %eax
	pushl	%eax
	pushl	$.LC12
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	$.LC13
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	$.LC14
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	20(%ebp)
	pushl	$.LC15
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	24(%ebp)
	pushl	$.LC16
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC17
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC18
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-8(%ebp), %eax
	pushl	%eax
	pushl	$.LC19
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-8(%ebp)
	pushl	$.LC20
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$jj.1
	pushl	$.LC21
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	jj.1
	pushl	$.LC22
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC23
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	test2,.Lfe2-test2
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
	pushl	$5
	call	test
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe3:
	.size	main,.Lfe3-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
