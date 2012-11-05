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
	subl	$4008, %esp
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
	leal	-4008(%ebp), %eax
	pushl	%eax
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4008(%ebp), %eax
	pushl	%eax
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
	leal	-4008(%ebp), %eax
	movl	%eax, addr
	subl	$12, %esp
	pushl	$.LC6
	call	printf
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
	.local	j.1
	.comm	j.1,4,4
	.section	.rodata
.LC7:
	.string	"<func1> &para = 0x%x \n"
.LC8:
	.string	"<func1> para = 0x%x \n"
.LC9:
	.string	"<func1> &testi = 0x%x \n"
.LC10:
	.string	"<func1> testi = 0x%x \n"
.LC11:
	.string	"<func1> &testj = 0x%x \n"
.LC12:
	.string	"<func1> testj = 0x%x \n"
.LC13:
	.string	"<func1> &j = 0x%x \n"
.LC14:
	.string	"<func1> j = 0x%x \n"
	.text
.globl test1
	.type	test1,@function
test1:
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
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC10
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-8(%ebp), %eax
	pushl	%eax
	pushl	$.LC11
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-8(%ebp)
	pushl	$.LC12
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$j.1
	pushl	$.LC13
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	j.1
	pushl	$.LC14
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	test1,.Lfe2-test1
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
	movl	addr, %eax
	movl	$13124, (%eax)
	movl	addr, %eax
	subl	$4, %eax
	movl	$21862, (%eax)
	subl	$12, %esp
	pushl	$6
	call	test1
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe3:
	.size	main,.Lfe3-main
	.local	jj.2
	.comm	jj.2,4,4
	.section	.rodata
.LC15:
	.string	"<func2> &para = 0x%x \n"
.LC16:
	.string	"<func2> para = 0x%x \n"
.LC17:
	.string	"<func2> &p2 = 0x%x \n"
.LC18:
	.string	"<func2> &p3 = 0x%x \n"
.LC19:
	.string	"<func2> &p4 = 0x%x \n"
.LC20:
	.string	"<func2> &p5 = 0x%x \n"
.LC21:
	.string	"<func2> p2 = 0x%x \n"
.LC22:
	.string	"<func2> p3 = 0x%x \n"
.LC23:
	.string	"<func2> p4 = 0x%x \n"
.LC24:
	.string	"<func2> p5 = 0x%x \n"
.LC25:
	.string	"<func2> &k1 = 0x%x \n"
.LC26:
	.string	"<func2> k1 = 0x%x \n"
.LC27:
	.string	"<func2> &k2 = 0x%x \n"
.LC28:
	.string	"<func2> k2 = 0x%x \n"
.LC29:
	.string	"<func2> &jj = 0x%x \n"
.LC30:
	.string	"<func2> jj = 0x%x \n"
.LC31:
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
	pushl	$.LC15
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	$.LC16
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	12(%ebp), %eax
	pushl	%eax
	pushl	$.LC17
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	16(%ebp), %eax
	pushl	%eax
	pushl	$.LC18
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	20(%ebp), %eax
	pushl	%eax
	pushl	$.LC19
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	24(%ebp), %eax
	pushl	%eax
	pushl	$.LC20
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	$.LC21
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	16(%ebp)
	pushl	$.LC22
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	20(%ebp)
	pushl	$.LC23
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	24(%ebp)
	pushl	$.LC24
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC25
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-4(%ebp)
	pushl	$.LC26
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-8(%ebp), %eax
	pushl	%eax
	pushl	$.LC27
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-8(%ebp)
	pushl	$.LC28
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$jj.2
	pushl	$.LC29
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	jj.2
	pushl	$.LC30
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC31
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe4:
	.size	test2,.Lfe4-test2
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
