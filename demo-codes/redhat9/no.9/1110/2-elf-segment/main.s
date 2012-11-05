	.file	"main.c"
.globl var1
	.data
	.align 4
	.type	var1,@object
	.size	var1,4
var1:
	.long	16
.globl var2
	.align 4
	.type	var2,@object
	.size	var2,4
var2:
	.long	18
.globl addr
	.align 4
	.type	addr,@object
	.size	addr,4
addr:
	.long	0
.globl chvar
	.type	chvar,@object
	.size	chvar,10
chvar:
	.ascii	"aabbccddab"
.globl ch
	.type	ch,@object
	.size	ch,1
ch:
	.byte	65
	.align 4
	.type	sta,@object
	.size	sta,4
sta:
	.long	-2
.globl ch1
	.type	ch1,@object
	.size	ch1,1
ch1:
	.byte	66
	.align 4
	.type	s.0,@object
	.size	s.0,4
s.0:
	.long	200
	.section	.rodata
.LC0:
	.string	"&local = 0x%x \n"
.LC1:
	.string	"&s = 0x%x \n"
	.text
.globl fun
	.type	fun,@function
fun:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$8, %esp
	movl	$100, -4(%ebp)
	movl	$4626, s.0
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$s.0
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	leave
	ret
.Lfe1:
	.size	fun,.Lfe1-fun
	.section	.rodata
.LC2:
	.string	"hello, Cruel World! \n"
.LC3:
	.string	"&bss0 = 0x%x \n"
.LC4:
	.string	"&bss1 = 0x%x \n"
.LC5:
	.string	"&bss2 = 0x%x \n"
.LC6:
	.string	"&ret1 = 0x%x \n"
.LC7:
	.string	"&ret2 = 0x%x \n"
.LC8:
	.string	"&var1 = 0x%x \n"
.LC9:
	.string	"&var2 = 0x%x \n"
.LC10:
	.string	"&addr = 0x%x \n"
.LC11:
	.string	"chvar = %s \n"
.LC12:
	.string	"&sta = 0x%x \n"
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
	movl	$0, -4(%ebp)
	movl	$23, -8(%ebp)
	subl	$12, %esp
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$bss0
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$bss1
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$bss2
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-4(%ebp), %eax
	pushl	%eax
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	leal	-8(%ebp), %eax
	pushl	%eax
	pushl	$.LC7
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var1
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var2
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$addr
	pushl	$.LC10
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$chvar
	pushl	$.LC11
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$sta
	pushl	$.LC12
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe2:
	.size	main,.Lfe2-main
	.comm	bss0,4,4
	.comm	bss1,4,4
	.comm	bss2,4,4
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
