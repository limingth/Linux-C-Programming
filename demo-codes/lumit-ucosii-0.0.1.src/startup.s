;/*
; *	startup.s  --   startup file for C_Entry
; *	
; *	Author: 	lumit-admin <admin@lumit.org>
; *	Date:		2004-8-26
; *	Copyright:	http://www.lumit.org
; */
; *********************************************************************
; *
; * ARM Strategic Support Group
; *
; *********************************************************************

; *********************************************************************
; *
; * Module		: startup.s
; * Description : used to initialize the embedded C library
; * Tool Chain	: ARM Developer Suite v1.0
; * Platform	: Evaluator7T
; * History		:
; *
; *		980416 ASloss
; *		- alter stack to point to 0x20000 (128k)
; *		- added headers
; *
; *		2000-04-04 Andrew N. Sloss
; *		- ported to Evaluator7T		
; *
; *		2000-04-07 HSH
; *		- Enable the interrupt bit
; *
; * Notes 	: This code was taken from ARM SDT 2.11 User Guide, 
; *               section 13.3
; *
; *********************************************************************

F_Bit		EQU 	0x40
Mode_Svc	EQU	0x13
	
	AREA asm_code, CODE

; *********************************************************************	
; * If assembled with TASM the variable {CONFIG} will be set to 16
; * If assembled with ARMASM the variable {CONFIG} will be set to 32
; * Set the variable THUMB to TRUE or false depending on whether the
; * file is being assembled with TASM or ARMASM.
; *********************************************************************	

	GBLL THUMB
	[ {CONFIG} = 16

THUMB SETL {TRUE}
	
; *********************************************************************
; * If assembling with TASM go into 32 bit mode as the Armulator will
; * start up the program in ARM state.
; *********************************************************************

	CODE32
	|
THUMB SETL {FALSE}
	]
	
	IMPORT C_Entry
; added by liming 2003-03-04
	IMPORT __rt_stackheap_init
	IMPORT __rt_lib_init 
		
	ENTRY
|__init|

; **********************************************************************
; * Set up the stack pointer to point to the 512K (Evaluator7T top of 
; * memory).
; **********************************************************************

	;set up irq stack
	mov 	r0, #0xd2               ; make irq mode with all irqs disabled
	msr 	cpsr_cxsf, r0
	MOV sp, #0x70000
	
	;set up svc stack
    	mov	r0, #0xd3                ; make svc mode with all irqs disabled
	msr	cpsr_cxsf, r0		 
	MOV sp, #0x80000
	

; **********************************************************************
; * Get the address of the C entry point.
; **********************************************************************
; added by liming 2003-03-04
;	bl       __rt_stackheap_init
;	bl       __rt_lib_init
	
	LDR lr, =C_Entry
	
; **********************************************************************
; * Enable the interrupt while staying in the supervisor mode
; **********************************************************************
	
	MOV	r0, #Mode_Svc:OR:F_Bit
	MSR	cpsr_c, r0
	
	[ THUMB

; **********************************************************************
; * If building a Thumb version pass control to C_entry using the BX
; * instruction so the processor will switch to THUMB state.
; **********************************************************************

	BX lr
	|

; **********************************************************************
; * Otherwise just pass control to C_Entry in ARM state.
; **********************************************************************

	MOV pc, lr
	]
	 
	END

; **********************************************************************
; * END OF startup.s
; **********************************************************************
 
