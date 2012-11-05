	INCLUDE	s3c4510.s
	
RomBaseAddr	EQU		0
RomEndAddr	EQU		&20
RamBaseAddr	EQU		&100
RamEndAddr	EQU		&200	
	
	AREA	text, CODE, READONLY	

SFR_BASE	EQU		0x3ff	;0x3ff0000
SRAM_BASE	EQU		0x3f8	;0x3f80000
	
	;EXPORT	InitMemory
InitMemory
	ldr	r0, =SYSCFG
	ldr	r1, =SDRAM_ITF :OR: SFR_BASE<<16 :OR: SRAM_BASE<<6 :OR: CACHE_ALL :OR: CACHE_EN	
	str	r1, [r0]
	
	ldr	r0, =CLKCON
	ldr	r1, =0
	str	r1, [r0]
	
	ldr	r0, =EXTACON0
	ldr	r1, =0x0fff0fff
	str	r1, [r0]
	ldr	r0, =EXTACON1
	ldr	r1, =0x0fff0fff	
	str	r1, [r0]
	
	ldr	r0, =EXTDBWTH
	ldr	r1, =0xffff556
	str r1, [r0]
	
	adr	r0, MemCfgPara
	ldmia	r0, {r1-r11}
	ldr	r0, =ROMCON0	
	stmia	r0, {r1-r11}
	
	mov	pc, r14
	
MemCfgPara
	DCD	RomBaseAddr<<10 :OR RomEndAddr<<20 :OR: &60	;&10840060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	RamBaseAddr<<10 :OR: RamEndAddr<<20 :OR: &398	;&10000398
	DCD	&10040398
	DCD	&10040398
	DCD	&10040398
	DCD	&ce2983fd		 		
	
	EXPORT	RemapMemory
RemapMemory
	adr	r0, RemapMemPara
	ldmia	r0, {r1-r11}
	ldr	r0, =ROMCON0
	stmia	r0, {r1-r11}
	nop
	nop
	ldr	r0, =IRQ_SVC_VECTOR
	ldr	r1, =IRQ_SERVICE		;IRQ_SVC_VECTOR in ram, so set it after remap
	str r1, [r0]
	
	mov	pc, r14	

RemapMemPara
	DCD	&12040060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10842060
	DCD	&10000398
	DCD	&10040398
	DCD	&10040398
	DCD	&10040398
	DCD	&ce2983fd		

	EXPORT	ResetMemSet
ResetMemSet
	adr	r0, ResetMemPara
	ldmia	r0, {r1-r11}
	ldr r0, =ROMCON0
	stmia	r0, {r1-r11}
	nop
	nop
	
	mov	pc, r14	
			
ResetMemPara
	DCD	&20000060
	DCD	&00000060
	DCD	&00000060
	DCD	&00000060
	DCD	&00000060
	DCD	&00000060
	DCD	&00000000
	DCD	&00000000
	DCD	&00000000
	DCD	&00000000
	DCD	&000083fd	

;*************************************************
InitInterrupt
	ldr	r0, =INTMSK
	ldr	r1, =0x3fffff
	str	r1, [r0]		;disable all interrupt
	
	mov	pc,	r14	

;*************************************************
InitPort
	ldr	r0, =IOPMOD
	ldr	r1, =1
	str	r1, [r0]		;all input but p0 output
	
	ldr	r0, =IOPCON
	ldr	r1, =0
	str	r1, [r0]		;disable XIRQ 0-3, dma req,ack, timer 0,1 output
	
	ldr	r0, =IOPDATA
	ldr r1, [r0]		;read input data
	
	mov	pc, r14	

;*************************************************
InitTimer
	ldr	r0, =TMOD
	ldr	r1, =0
	str	r1, [r0]		;disable timer 0,1
	
	mov	pc, r14

;*************************************************
UART_DIV_CNT0	EQU	26
UART_DIV_CNT1	EQU	0

InitUart
	ldr	r0, =ULCON0
	ldr	r1, =DATA8b :OR: STOPb1 :OR PARITY_NO
	str	r1, [r0]
	
	ldr	r0, =UCON0
	ldr	r1, =RX_STAT_INT|9
	str	r1, [r0]
	
	ldr	r0, =UBRDIV0
	ldr	r1, =UART_DIV_CNT0<<4|UART_DIV_CNT1
	str	r1, [r0]		;if UART_DIV_CNT1==xxx0 baud rate = MCLK/(UART_DIV_CNT0+1)/16
						;if UART_DIV_CNT1==xxx1 baud rate = MCLK/(UART_DIV_CNT0+1)/16/16	
	ldr	r0, =URXBUF0
	ldr	r1, [r0]		;read rx data
	
	ldr	r0, =ULCON1
	ldr	r1, =DATA8b :OR: STOPb1 :OR PARITY_NO
	str	r1, [r0]
	
	ldr	r0, =UCON1
	ldr	r1, =RX_STAT_INT|9
	str	r1, [r0]
	
	ldr	r0, =UBRDIV1
	ldr	r1, =UART_DIV_CNT0<<4|UART_DIV_CNT1
	str	r1, [r0]		;if UART_DIV_CNT1==xxx0 baud rate = MCLK/(UART_DIV_CNT0+1)/16
						;if UART_DIV_CNT1==xxx1 baud rate = MCLK/(UART_DIV_CNT0+1)/16/16	
	ldr	r0, =URXBUF1
	ldr	r1, [r0]		;read rx data
	
	mov	pc, r14
	
;*************************************************	
InitStack
	mrs	r0, cpsr
	bic	r0, r0, #PSR_MODE_MASK
	
	orr	r1, r0, #PSR_UNDEF_MODE|NO_INT
	msr	cpsr_cxsf, r1		;UndefMode
	ldr	sp,=UndefStack
	
	orr	r1, r0, #PSR_ABORT_MODE|NO_INT
	msr	cpsr_cxsf, r1		;AbortMode
	ldr	sp, =AbortStack
	
	orr	r1, r0, #PSR_IRQ_MODE|NO_INT
	msr	cpsr_cxsf, r1		;IRQMode
	ldr	sp, =IRQStack
	
	orr	r1, r0, #PSR_FIQ_MODE|NO_INT
	msr	cpsr_cxsf, r1		;FIQMode
	ldr	sp, =FIQStack	
		
	orr	r1, r0, #PSR_SVC_MODE|NO_INT
	msr	cpsr_cxsf, r1		;SVCMode
	ldr	sp, =SVCStack
	
	mov	pc, r14

;*************************************************
	EXPORT	InitSystem	
InitSystem
	mov	r12, r14
	bl	InitMemory
	bl	InitStack
	bl	InitPort
	bl	InitUart
	bl	InitTimer
	bl	InitInterrupt
;	ldr	r0, =0x11000000         ;Cache Flush 
;	mov	r1, #0
;	mov	r2, #256                
;1
;	str	r1, [r0], #4
;	subs	r2, r2, #1
;	bne	%B1	
	mov	pc, r12	
	
;*************************************************
IRQ_SERVICE				;using I_ISPR register.		   	
	IMPORT	pIrqStart
	IMPORT	pIrqFinish
	IMPORT	pIrqHandler	
	
			;nop
			;ldr	r0, =TMOD
			;ldr	r1,	[r0]
			;and	r1,	r1, #&37
			;str	r1, [r0]
							
	ldr	r4, =INTOFFSET
   	ldr	r4, [r4]
   	mov	r1, r4, lsr #2
   	mov	r0, #1
   	mov	r0, r0, lsl r1
   	ldr	r1, =INTPND
   	str	r0, [r1]		;clear interrupt pending bit
   	ldr	r1, =pIrqStart
   	ldr	r1, [r1]
   	cmp	r1, #0
   	movne	lr, pc		; .+8
   	movne	pc, r1    		    	        	
	
   	ldr	r1, =pIrqHandler
   	ldr	r1, [r1]
   	cmp	r1, #0
   	movne	lr, pc
   	movne	pc, r1     	    	   	
	
	ldr	r1, =pIrqFinish
	ldr	r1, [r1]
	cmp	r1, #0
	movne	lr, pc		; .+8
	movne	pc, r1
	cmp	r0, #0
	movne	lr, pc
	movne	pc, r0 					
	
	ldmfd	sp!, {r0}	;´ÓIRQ·µ»Ø
	msr	spsr_cxsf, r0
	ldmfd	sp!, {r0-r12, pc}^		
;*************************************************
	AREA HiVector, DATA, READWRITE
	
_RAM_END_ADDR	EQU	0x01000000		

	^	(_RAM_END_ADDR-0x600)				
UserStack	#	256	;xxxxxa00
SVCStack	#	256	;xxxxxb00
UndefStack	#	256	;xxxxxc00
AbortStack	#	256	;xxxxxd00
IRQStack	#	256	;xxxxxe00
FIQStack	#	0	;xxxxxf00


	MAP	(_RAM_END_ADDR-0x100)
SYS_RST_VECTOR	#	4	
UDF_INS_VECTOR	#	4	
SWI_SVC_VECTOR	#	4
INS_ABT_VECTOR	#	4
DAT_ABT_VECTOR	#	4
RESERVED_VECTOR	#	4
IRQ_SVC_VECTOR	#	4
FIQ_SVC_VECTOR	#	4

	EXPORT	SYS_RST_VECTOR
	EXPORT	UDF_INS_VECTOR
	EXPORT	SWI_SVC_VECTOR
	EXPORT	INS_ABT_VECTOR
	EXPORT	DAT_ABT_VECTOR
	EXPORT	RESERVED_VECTOR
	EXPORT	IRQ_SVC_VECTOR
	EXPORT	FIQ_SVC_VECTOR
	
;*************************************************	
	END	