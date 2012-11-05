;/*
; *	irq_ven.s  --   button irq handler code    
; *	
; *	Author: 	lumit-admin <admin@lumit.org>
; *	Date:		2004-8-26
; *	Copyright:	http://www.lumit.org
; */
	IMPORT timer_irq
	EXPORT handler_irq
	EXPORT Angel_IRQ_Address
	
	AREA	irq, CODE, READONLY

; ********************************************************************************
; * DATA
; ********************************************************************************
INTPND		DCD		0x03ff4004				;IRQ controller

handler_irq
	STMFD	sp!, {r0 - r3, LR}	;Maintain Stack using APCS standard

	; -- identify source of interrupt .........................
	LDR 	r0, INTPND	 
	LDR 	r0, [r0]		

	; -- check if source is a timer interrupt .................
	TST 	r0, #0x0400
	BNE	handler_event_timer 

	LDMFD	sp!, {r0 - r3, lr}		;If not then its an Angel request
	LDR 	pc, Angel_IRQ_Address	;remove the regs from the stack and call 
					;the routine
			

handler_event_timer
	BL	timer_irq				;if this point is reached then the irq is from 
							;the timer
	LDMFD   sp!, {r0 - r3,lr}	;return from the irq_auxtimer routine - 
							;restore the registers 
	subs    pc, lr, #4 			;and return from the interrupt

Angel_IRQ_Address	
	DCD 0x00000000				; Scratch location for Angel IRQ Handler address


	END
