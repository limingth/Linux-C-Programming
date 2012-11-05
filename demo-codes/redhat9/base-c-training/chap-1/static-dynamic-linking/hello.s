	.file	"hello.cpp"
	.section	.rodata
.LC0:
	.string	"hello, Cruel World! \n"
	.text
	.align 2
.globl main
	.type	main,@function
main:
.LFB2:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	subl	$8, %esp
.LCFI2:
	andl	$-16, %esp
	movl	$0, %eax
	subl	%eax, %esp
	subl	$12, %esp
	pushl	$.LC0
.LCFI3:
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.LFE2:
.Lfe1:
	.size	main,.Lfe1-main
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
