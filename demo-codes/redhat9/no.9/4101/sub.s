	.file	"sub.c"
	.text
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
.Lfe1:
	.size	sub,.Lfe1-sub
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
