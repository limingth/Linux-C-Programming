/*
 *	os_cpu_c.c --   the porting code for Evaluator-7T
 *	
 *	Author: 	lumit-admin <admin@lumit.org>
 *	Date:		2004-8-26
 *	Copyright:	http://www.lumit.org
 */

/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                          All Rights Reserved
*                        (c) Copyright ARM Limited 1999.  All rights reserved.
*
*                                          ARM Specific code
*
*
* File : OS_CPU_C.C
*********************************************************************************************************
*/

#define  OS_CPU_GLOBALS
#include "includes.h"

/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*
* Note(s)    : Interrupts are enabled when your task starts executing. You can change this by setting the
*              PSW to 0x0002 instead.  In this case, interrupts would be disabled upon task startup.  The
*              application code would be responsible for enabling interrupts at the beginning of the task
*              code.  You will need to modify OSTaskIdle() and OSTaskStat() so that they enable 
*              interrupts.  Failure to do this will make your system crash!
*********************************************************************************************************
*/

OS_STK * OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    unsigned int *stk;

    opt    = opt;                           /* 'opt' is not used, prevent warning                      */
    stk    = (unsigned int *)ptos;          /* Load stack pointer                                      */

    /* build a context for the new task */
    *--stk = (unsigned int) task;       /* pc */
    *--stk = (unsigned int) task;       /* lr */

    *--stk = 0;                         /* r12 */
    *--stk = 0;                         /* r11 */
    *--stk = 0;                         /* r10 */
    *--stk = 0;                         /* r9 */
    *--stk = 0;                         /* r8 */
    *--stk = 0;                         /* r7 */
    *--stk = 0;                         /* r6 */
    *--stk = 0;                         /* r5 */
    *--stk = 0;                         /* r4 */
    *--stk = 0;                         /* r3 */
    *--stk = 0;                         /* r2 */
    *--stk = 0;                         /* r1 */
    *--stk = (unsigned int) pdata;      /* r0 */
    *--stk = (SVC32MODE|0x40);			/* cpsr  FIQ disable*/
    *--stk = (SVC32MODE|0x40);			/* spsr  FIQ disable */


    return ((void *)stk);
}

/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
#if 0
	printf("------------------------------------------\n");
	printf("\t\tOSTCBCur\tOSTCBHighRdy\n");
	printf("OSTCBPrio:\t%d\t\t%d\n",OSTCBCur->OSTCBPrio,OSTCBHighRdy->OSTCBPrio);
	printf("OSTCBStkPtr:\t%p\t%p\n",OSTCBCur->OSTCBStkPtr,OSTCBHighRdy->OSTCBStkPtr);
//	printf("OSTCBEventPtr:\t%p\t%p\n",OSTCBCur->OSTCBEventPtr,OSTCBHighRdy->OSTCBEventPtr);
//	printf("OSTCBMsg:\t%p\t%p\n",OSTCBCur->OSTCBMsg,OSTCBHighRdy->OSTCBMsg);
	printf("Point:\t\t%p\t%p\n",OSTCBCur,OSTCBHighRdy);
	printf("OSTCBDly:\t%d\t\t%d\n",OSTCBCur->OSTCBDly,OSTCBHighRdy->OSTCBDly);
//	printf("OSTCBStat:\t%d\t%d\n",OSTCBCur->OSTCBStat,OSTCBHighRdy->OSTCBStat);

//	printf("OSTCBX:\t\t%d\t%d\n",OSTCBCur->OSTCBX,OSTCBHighRdy->OSTCBX);
//	printf("OSTCBY:\t\t%d\t%d\n",OSTCBCur->OSTCBY,OSTCBHighRdy->OSTCBY);
//	printf("OSTCBBitX:\t%d\t%d\n",OSTCBCur->OSTCBBitX,OSTCBHighRdy->OSTCBBitX);
//	printf("OSTCBBitY:\t%d\t%d\n",OSTCBCur->OSTCBBitY,OSTCBHighRdy->OSTCBBitY);
#endif
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
	printf ( "OSTaskStatHook \n" );
}

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/

void OSTimeTickHook (void)
{
#if 0
	OS_TCB    *ptcb;
	ptcb = OSTCBList;                                      /* Point at first TCB in TCB list           */

	printf( "\n############### OSTimeTickHook ###################\n" );
	printf( "*****************************************\n" );
    while (ptcb->OSTCBPrio != OS_IDLE_PRIO) 
    {              /* Go through all TCBs in TCB list          */
        OS_ENTER_CRITICAL();
    	printf( "ptcb->OSTCBPrio = %d   ", ptcb->OSTCBPrio );
		printf("ptcb->OSTCBStkPtr = %p   ",ptcb->OSTCBStkPtr);
    	printf( "ptcb->OSTCBDly = %d    ", ptcb->OSTCBDly );    	
    	printf( "\n" );
        ptcb = ptcb->OSTCBNext;                                /* Point at next TCB in TCB list        */
        OS_EXIT_CRITICAL();
    }
    printf( "\n*****************************************\n" );
#endif
}
#endif

void InitHookEnd (void)
{
}

void OSTCBInitHook (OS_TCB *ptcb)
{
#if 0
    ptcb = ptcb;                                           /* Prevent Compiler warning  */  
  
    {              /* Go through all TCBs in TCB list          */
  		printf( "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n " );
    	printf( "ptcb->OSTCBPrio = %d   ", ptcb->OSTCBPrio );
		printf("ptcb->OSTCBStkPtr = %p ",ptcb->OSTCBStkPtr);
		printf( "ptcb->OSTCBDly = %d    ", ptcb->OSTCBDly );
        ptcb = ptcb->OSTCBNext;                                /* Point at next TCB in TCB list        */
   		printf( "\n ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n " );
    }
#endif          
}

void OSTaskIdleHook (void)
{
	static int counter = 0;
	int i, j;
	if ( counter++ > 100 )
	{
		for( i = 0; i < 65536; i++ )
			for ( j = 0; j < 65536; j++ )
					counter = 0;
	}	
}

void OSInitHookBegin (void)
{
	printf ( "OSInitHookBegin \n" );
}

void OSInitHookEnd (void)
{
	printf ( "OSInitHookEnd \n" );
}

void OS_FlagInit(void)
{
}

void          OS_FlagUnlink(OS_FLAG_NODE *pnode)
{
}

INT32U        OSIntCtxSwFlag = 0;           /* Used to flag a context switch */

