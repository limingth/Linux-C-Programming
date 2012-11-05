	.file	"main.c"
.globl var1
	.data
	.align 4
	.type	var1,@object
	.size	var1,4
var1:
	.long	16
.globl var3
	.align 4
	.type	var3,@object
	.size	var3,4
var3:
	.long	9
	.section	.rodata
.LC0:
	.string	"abcd"
.globl var5
	.data
	.align 4
	.type	var5,@object
	.size	var5,4
var5:
	.long	.LC0
.globl var7
	.section	.rodata
	.align 4
	.type	var7,@object
	.size	var7,4
var7:
	.long	100
.globl var8
	.data
	.type	var8,@object
	.size	var8,16
var8:
	.string	"ABCD"
	.zero	11
	.section	.rodata
.LC1:
	.string	"demo elf segment \n"
.LC2:
	.string	"&var1 = 0x%x \n"
.LC3:
	.string	"&var2 = 0x%x \n"
.LC4:
	.string	"&var3 = 0x%x \n"
.LC5:
	.string	"&var4 = 0x%x \n"
.LC6:
	.string	"&var5 = 0x%x \n"
.LC7:
	.string	"&var6 = 0x%x \n"
.LC8:
	.string	"&var7 = 0x%x \n"
.LC9:
	.string	"var8 = 0x%x \n"
.LC10:
	.string	"var5 = 0x%x \n"
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
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var1
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var2
	pushl	$.LC3
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var3
	pushl	$.LC4
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var4
	pushl	$.LC5
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var5
	pushl	$.LC6
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var6
	pushl	$.LC7
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var7
	pushl	$.LC8
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$var8
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	var5
	pushl	$.LC10
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	leave
	ret
.Lfe1:
	.size	main,.Lfe1-main
	.comm	var2,4,4
	.comm	var4,4,4
	.comm	var6,4,4
	.ident	"GCC: (GNU) 3.2.2 20030222 (Red Hat Linux 3.2.2-5)"
