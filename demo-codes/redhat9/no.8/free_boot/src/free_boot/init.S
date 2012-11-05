@*************************************************************
@	
@	Free bootloader for S3C4510B
@ 	Author: 	yu feng <progeryf@gmail.com>
@ 	Date:		2007-5-11
@	Modify:		2007-5-28	
@
@**************************************************************

#include "snds.h"

@Part 1
@***************************************************************
@disable interrupts in CPU and switch to SVC32 mode

.global _start

_start:

	mrs	r0, cpsr
	bic	r0, r0, #MASK_MODE			 @00111111 set the low 6 to 0
	orr	r0, r0, #MODE_SVC32			 @MODE_SVC32 00010011 
	orr r0, r0, #I_BIT				 @set the i bit to 1 disable the interrupts
	orr r0, r0, #F_BIT				 @set the f bit to 1 disable the fast interruputs
	msr	cpsr_c, r0					 @copy the r0 to cpsr 

/*just for testing*/
/*
loop:
	ldr r0, =0x03ff5000
	ldr r1, =0x0003ffff
	str r1, [r0]

	ldr r0, =0x03ff5008
	ldr r1, =0x00020000
	str r1, [r0]

	ldr r4, =__text_start 
	ldr r5, =__text_end 
	ldr r6, =__data_start 
	ldr r7, =__data_end 
	ldr r8, =__bss_start 
	ldr r9, =__bss_end 
*/
@set ARM7_INTMASK FFFFFFFF
	ldr	r2, =ARM7_INTMASK			 @R2->interrupt controller
	mvn	r1, #0						 @&FFFFFFFF
	str	r1, [r2]					 @disable all interrupt soucres

@set ARM7_INTPEND FFFFFFFF
	ldr	r2, =ARM7_INTPEND			 @R2->interrupt pend register.
	mvn	r1, #0						 @&FFFFFFFF
	str	r1, [r2]					 @clear all interrupt flags.


@Part 2
@****************************************************************

	ldr	r0, =ARM7_SYSCFG
	ldr	r1, =0x87fffe12				@config SYSCFG set ARM&_SYSCFG as 0x87ffffa0 
	str	r1, [r0] 					@Cache & WB disabled


@Part 3 
@****************************************************************
@Initalize the memory p22
@	FLASH			@ 0  ~ 2 M
@	SDRAM			@ 2  ~ 18M


	ldr	r1, =rEXTDBWTH 				@EXTDBWTH          		
	ldr	r2, =rROMCON0  				@ROMCON0	@ 0M ~ 2M	
	ldr	r3, =rROMCON1				@ROMCON1	@ DISABLED
	ldr	r4, =rROMCON2				@ROMCON1	@ DISABLED
	ldr	r5, =rROMCON3				@ROMCON1	@ DISABLED
	ldr	r6, =rROMCON4				@ROMCON1	@ DISABLED
	ldr	r7, =rROMCON5				@ROMCON1	@ DISABLED
	ldr	r8, =rSDRAMCON0				@SDRAMCON0 	@ 2M ~ 18M
	ldr	r9, =rSDRAMCON1				@SDRAMCON1 	@ DISABLED
	ldr	r10,=rSDRAMCON2				@SDRAMCON2 	@ DISABLED
	ldr	r11,=rSDRAMCON3				@SDRAMCON3 	@ DISABLED
	ldr	r12,=rSREFEXTCON			
	
	ldr	r0, =ARM7_EXTDBWTH 	
	stmia	r0, {r1-r12}

/* just for testing
loo:
@	ldr	sp, =0x240000  

	ldr r3, =0x20030
	ldr r4, =0x210000
	str r3, [r4]

	ldr r0, =0x3ff5008
	ldr r1, [r4]
	str r1, [r0]
	b loo
*/
@	ldr		pc, =load



@Part 4 
@***************************************************************
@Self copy from FLASH to SDRAM

	ldr		r0, =__text_start
	ldr		r1, =__text_end
	ldr		r2, =__data_start
	ldr		r3, =__data_end

	sub 	r1, r1, r0	@the size of RO
	sub		r3, r3, r2	@the size of RW
	add		r1, r1, r3	@the size of all
	
	ldr		r2, =0x200000   @2M

	
copy:
	ldr		r3, [r0], #4
	str		r3, [r2], #4
	subs	r1, r1,   #4
	bne		copy

/*just for testing
lo:
	ldr r3, =0x20030
	ldr r4, =0x210000
	str r3, [r4]

	ldr r0, =0x3ff5008
	ldr r1, [r4]
@	ldr r1, =0x20070
	str r1, [r0]
@	b lo
*/

 
@Part 5 
@***************************************************************
@Remap the memory
@ 	FLASH	@ 16 ~ 18M 
@ 	SDRAM	@ 0  ~ 16M


	ldr	r1, =rEXTDBWTH_R 			@EXTDBWTH          		
	ldr	r2, =rROMCON0_R  			@ROMCON0	@ 16M ~ 18M	
	ldr	r3, =rROMCON1_R				@ROMCON1	@ DISABLED
	ldr	r4, =rROMCON2_R				@ROMCON2	@ DISABLED
	ldr	r5, =rROMCON3_R				@ROMCON3	@ DISABLED
	ldr	r6, =rROMCON4_R				@ROMCON4	@ DISABLED
	ldr	r7, =rROMCON5_R				@ROMCON4	@ DISABLED
	ldr	r8, =rSDRAMCON0_R			@SDRAMCON0 	@ 0M ~ 16M
	ldr	r9, =rSDRAMCON1_R			@SDRAMCON1 	@ DISABLED
	ldr	r10,=rSDRAMCON2_R			@SDRAMCON2 	@ DISABLED
	ldr	r11,=rSDRAMCON3_R			@SDRAMCON3 	@ DISABLED
	ldr	r12,=rSREFEXTCON_R			

	ldr	r0, =ARM7_EXTDBWTH 			
	stmia	r0, {r1-r12}

/*
lo:
	ldr r3, =0x20010
	ldr r4, =0x210000
	str r3, [r4]

	ldr r0, =0x3ff5008
	ldr r1, [r4]
@	ldr r1, =0x20070
	str r1, [r0]
  	b lo
*/

@Part 6 

@*****************************************************************
@ Copy Data & ZI to SDRAM

	ldr r0, =__text_end
	ldr r1, =__data_start
	ldr r3, =__bss_start 		

	cmp r0, r1 
	beq 1f
 
0:	cmp r1, r3 						@ Copy init data
	ldrcc r2, [r0], #4
	strcc r2, [r1], #4
	bcc 0b

1:	ldr r1, =__bss_end 				@ Top of zero init segment
	mov r2, #0

2:	cmp r3, r1 						@ Zero init
	strcc r2, [r3], #4
	bcc 2b

@Part 7
@***********************************************************************
@Set stack pointer & jump to c function

	ldr		sp, =0x800000 @ Set the stack pointer 

	ldr		pc, =load	@ Jump to c function the assembly complete
