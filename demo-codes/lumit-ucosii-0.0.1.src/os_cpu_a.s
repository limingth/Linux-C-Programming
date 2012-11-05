;/*
; *	os_cpu_a.s  --  porting codes for Evaluator-7T
; *	
; *	Author: 	lumit-admin <admin@lumit.org>
; *	Date:		2004-8-26
; *	Copyright:	http://www.lumit.org
; */

;********************************************************************/
      AREA	|subr|, CODE, READONLY

;/***********************************************************************
;
; Function: OSStartHighRdy
;
; Purpose:
; 	   To start the task with the highest priority during OS startup
;
; Processing:
;    See uC/OS-II Task Level Context Switch flow chart
;
; Parameters: void
;
; Outputs:  None
;
; Returns:  void
;
; Notes:
;   Called once during OSStart()
;
;*********************************************************************/
	EXPORT 	OSStartHighRdy
	IMPORT	OSTaskSwHook
	IMPORT  OSTCBHighRdy 
	IMPORT  OSRunning
OSStartHighRdy
        BL 	OSTaskSwHook             ; Call user-defined hook function

        LDR 	r4,=OSRunning            ; Indicate that multitasking has started
        MOV 	r5, #1                   
        STRB 	r5, [r4]                 ; OSRunning = true

        LDR 	r4, =OSTCBHighRdy        ; Get highest priority task TCB address
        LDR 	r4, [r4]                 ; get stack pointer
        LDR 	sp, [r4]                 ; switch to the new stack

        LDMFD 	sp!, {r4}                ; pop new task s spsr_cxsf
        MSR 	spsr_cxsf, r4
        LDMFD 	sp!, {r4}                ; pop new task s psr
        MSR 	cpsr_cxsf, r4
        LDMFD 	sp!, {r0-r12,lr,pc}      ; pop new task s r0-r12,lr & pc

 	
;/***********************************************************************
;
; Function: OS_TASK_SW 
;
; Purpose:
; 	To perform a context switch from the Task Level.
;
; Processing:
;    See uC/OS-II Task Level Context Switch flow chart
;
; Parameters: void
;
; Outputs:  None
;
; Returns:  void
;
; Notes:
;   On entry, OSTCBCur and OSPrioCur hold the current TCB and priority
;   and OSTCBHighRdy and OSPrioHighRdy contain the same for the task
;   to be switched to.
; 
;   The following code assumes that the virtual memory is directly
;   mapped into  physical memory. If this is not true, the cache must 
;   be flushed at context switch to avoid address aliasing.
;
;*********************************************************************/
        EXPORT 	OSCtxSw
        IMPORT	OSPrioCur
        IMPORT	OSPrioHighRdy
        IMPORT	OSTCBCur
        IMPORT	OSTaskSwHook
        IMPORT	OSTCBHighRdy
        
OSCtxSw
        STMFD 	sp!, {lr}                ; push pc (lr is actually be pushed in place of PC)
        STMFD 	sp!, {r0-r12,lr}         ; push lr & register file
        MRS 	r4, cpsr
        STMFD 	sp!, {r4}                ; push current psr
        MRS 	r4, spsr
        STMFD 	sp!, {r4}                ; push current spsr_cxsf

_OSCtxSw
        LDR 	r4, =OSPrioCur           ; OSPrioCur = OSPrioHighRdy
        LDR 	r5, =OSPrioHighRdy
        LDRB 	r6, [r5]
        STRB 	r6, [r4]
        
        LDR 	r4, =OSTCBCur            ; Get current task TCB address
        LDR 	r5, [r4]
        STR 	sp, [r5]                 ; store sp in preempted tasks s TCB

        BL 	OSTaskSwHook             ; call Task Switch Hook

        LDR 	r6, =OSTCBHighRdy        ; Get highest priority task TCB address
        LDR 	r6, [r6]
        LDR 	sp, [r6]                 ; get new task s stack pointer

        STR 	r6, [r4]                 ; set new current task TCB address

        LDMFD 	sp!, {r4}                ; pop new task spsr_cxsf
        MSR 	spsr_cxsf, r4
        LDMFD 	sp!, {r4}                ; pop new task cpsr
        MSR 	cpsr_cxsf, r4
        LDMFD 	sp!, {r0-r12,lr,pc}      ; pop new task r0-r12,lr & pc


;***********************************************************************
;
; Function: OSIntCtxSw
;
; Purpose:
; 	To perform a context switch from the interrupt level.
;
; Processing:
;    See uC/OS-II Interrupt Level Context Switch flow chart
;
; Parameters: void
;
; Outputs:  None
;
; Returns:  void
;
; Notes:
;   Sets up the stacks and registers to call the task level
;   context switch
;
;*********************************************************************/
        EXPORT 	OSIntCtxSw
        IMPORT	OSIntCtxSwFlag
OSIntCtxSw
        LDR 	r0, =OSIntCtxSwFlag      ; OSIntCtxSwFlag = true
        MOV 	r1, #1
        STR 	r1, [r0]
        
        MOV 	pc, lr                   ; return 

;/***********************************************************************
;
;yangye 2003-2-14
;changed this function name from OSTickISR to OSISR(it is not a TICK isr)
; Function: OSISR
;
; Purpose:
; 	   The IRQ interrupt handler
;
; Processing:
;    Saves context
;    Calls the IRQ dispatcher
;    Checks if context switch necessary
;    If not, restores context and returns from interrupt
;    If switch required, branches without link to IRQContextSwap
;       which performs context switch if interrupts not nested
;       and returns from interrupt to new context
;
; Parameters: void
;
; Outputs:  None
;
; Returns:  void
;
; Notes:
;   (1) here we use OSIntCtxSwFlag to indicate a request for int-level 
;       context switch 
;   (2) _IntCtxSw is used to perform a real switch operation
;
;*********************************************************************/	

SAVED_LR_SVC	DCD   0x00000000        ; some variables for temparal use
SAVED_LR_IRQ	DCD   0x00000000
SAVED_SPSR		DCD	  0x00000000

INTPND		DCD		0x03ff4004				;IRQ controller

	EXPORT 	OSTickISR
	IMPORT	OSIntEnter
	IMPORT	OSTimeTick
	IMPORT	timer_irq
	IMPORT	OSIntExit
	IMPORT	OSIntCtxSwFlag
	
OSTickISR
	SUB	lr, lr, #4            
	STMFD	sp!, {r0-r12, lr}        ; push r0-r12 register file and lr( pc return address )
 
    MRS 	r4, spsr        
	STMFD 	sp!, {r4}                ; push current spsr_cxsf_irq ( =cpsr_svc )

	; -- identify source of interrupt .........................
	LDR 	r0, INTPND	 
	LDR 	r0, [r0]		
	
	TST 	r0, #0x0400
	BNE	handler_event_timer 		
	
    LDMFD 	sp!, {r4}                ; get cpsr_svc from stack
	MSR     spsr_cxsf, r4                 ; prepare spsr_cxsf to return svc mode	
	LDMFD	sp!, {r0-r12, pc}^       ; recover r0-r12 and pc from stack, cpsr also

handler_event_timer 

	BL	OSIntEnter

	BL 	OSTimeTick
	BL	timer_irq  	                 ; here do_IRQ is used to clear some virtual-hardware flags
	BL	OSIntExit
	
	LDR	r0, =OSIntCtxSwFlag      ; check if OSIntCtxFlag is marked as true
	LDR 	r1, [r0]
	CMP	r1, #1
	
	BEQ	_IntCtxSw	         ; if OSIntCtxFlag = true, then jump to _IntCtxSw



_IntCtxSw
        MOV 	r1, #0                   ; clear OSIntCtxSwFlag = flase
        STR 	r1, [r0]
	
        LDMFD 	sp!, {r4}                ; restore spsr_cxsf_irq 
	MSR 	spsr_cxsf, r4 	
    str		r4, SAVED_SPSR
	LDMFD	sp!, {r0-r12, lr}        ; recover the irq stack pointer

	STR	lr, SAVED_LR_IRQ         ; save lr_irq to SAVED_LR_IRQ 	
	MOV	lr, #0x000000d3          ; change forcely cpsr to svc mode
	MSR	cpsr_cxsf, lr	
	STR     lr, SAVED_LR_SVC         ; save lr_svc to SAVED_LR_SVC
	LDR	lr, SAVED_LR_IRQ         ; get lr_irq value saved in SAVED_LR_IRQ 
	STMFD 	sp!, {lr}                ; push future task pc (lr_irq should be pushed in place of PC)
	LDR	lr, SAVED_LR_SVC         ; get lr_svc value saved in SAVED_LR_SVC 

        STMFD 	sp!, {r0-r12,lr}         ; push lr & r0-r12 register file
        ldr		r4, SAVED_SPSR
		 ;	    MRS 	r4, spsr
        STMFD 	sp!, {r4}                ; push current psr
		  ;     MRS 	r4, spsr
        STMFD 	sp!, {r4}                ; push spsr_cxsf

	B	_OSCtxSw                 ; jump to _OSCtxSw	
	
	
	
;/***********************************************************************
;
; Functions: ARMDisableInt
; 	     ARMEnableInt
;
; Purpose:
;    Disable and enable IRQ and FIQ preserving current CPU mode.
;
; Processing:
;    Push the cpsr onto the stack
;    Disable IRQ and FIQ interrupts
;    Return 
;
; Parameters: void
;
; Outputs:  None
;
; Returns:  void
;
; Notes:
;   (1) Can be called from SVC mode to protect Critical Sections. 
;   (2) Do not use these calls at interrupt level.
;   (3) Used in pairs within the same function level;
;   (4) Will restore interrupt state when called; i.e., if interrupts
;       are disabled when DisableInt is called, interrupts will still
;       still be disabled when the matching EnableInt is called.
;   (5) Uses the method described by Labrosse as "Method 2".
;
;*********************************************************************/
        EXPORT 	ARMDisableInt
ARMDisableInt
	MRS	r0, cpsr
	STMFD	sp!, {r0}	         ; push current PSR
	ORR	r0, r0, #0xC0
	MSR	cpsr_c, r0		 ; disable IRQ Int s

	MOV	pc, lr


    ;------------------------------------------------------------------------
        EXPORT 	ARMEnableInt
ARMEnableInt
	LDMFD	sp!, {r0}                ; pop current PSR
	MSR	cpsr_c, r0               ; restore original cpsr	

	MOV	pc, lr
    ;------------------------------------------------------------------------
    	
	END