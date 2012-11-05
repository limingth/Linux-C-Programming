# get the max num from array

.section .data
data_items:
.long 3, 67, 34, 222, 45, 75, 54, 34, 44, 33, 22, 11, 66, 0

.section .text
.global _start
_start:
	# max = a[0]
	movl $0, %edi
	movl data_items(, %edi, 4), %eax
	movl %eax, %ebx

start_loop:
	cmpl $0, %eax
	je loop_exit

	# if (max > a[i])
	incl %edi
	movl data_items(, %edi, 4), %eax
	cmpl %ebx, %eax
	jle start_loop

	# max < a[i] : max = a[i]
	movl %eax, %ebx
	jmp start_loop

loop_exit:
	movl $1, %eax
	# %ebx : max
	int $0x80


	



















