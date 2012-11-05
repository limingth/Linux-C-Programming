	.file	"add.c"
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
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
