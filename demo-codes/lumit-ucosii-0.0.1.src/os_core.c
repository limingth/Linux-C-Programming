/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                             CORE FUNCTIONS
*
*                          (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : OS_CORE.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#define  OS_GLOBALS
#include "includes.h"
#endif

/*
*********************************************************************************************************
*                              MAPPING TABLE TO MAP BIT POSITION TO BIT MASK
*
* Note: Index into table is desired bit position, 0..7
*       Indexed value corresponds to bit mask
*********************************************************************************************************
*/

INT8U  const  OSMapTbl[]   = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

/*
*********************************************************************************************************
*                                       PRIORITY RESOLUTION TABLE
*
* Note: Index into table is bit pattern to resolve highest priority
*       Indexed value corresponds to highest priority bit position (i.e. 0..7)
*********************************************************************************************************
*/

INT8U  const  OSUnMapTbl[] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0
};
/*$PAGE*/
/*
*********************************************************************************************************
*                                             INITIALIZATION
*
* Description: This function is used to initialize the internals of uC/OS-II and MUST be called prior to
*              creating any uC/OS-II object and, prior to calling OSStart().
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

void  OSInit (void)
{
    INT16U     i;
    INT8U     *prdytbl;
    OS_TCB    *ptcb1;
    OS_TCB    *ptcb2;
#if (OS_EVENT_EN > 0) && (OS_MAX_EVENTS > 1)
    OS_EVENT  *pevent1;
    OS_EVENT  *pevent2;
#endif


#if OS_VERSION >= 204
    OSInitHookBegin();                                           /* Call port specific initialization code   */
#endif

#if OS_TIME_GET_SET_EN > 0   
    OSTime        = 0L;                                          /* Clear the 32-bit system clock            */
#endif
    OSIntNesting  = 0;                                           /* Clear the interrupt nesting counter      */
    OSLockNesting = 0;                                           /* Clear the scheduling lock counter        */
    OSTaskCtr     = 0;                                           /* Clear the number of tasks                */
    OSRunning     = FALSE;                                       /* Indicate that multitasking not started   */
    OSIdleCtr     = 0L;                                          /* Clear the 32-bit idle counter            */
#if (OS_TASK_STAT_EN > 0) && (OS_TASK_CREATE_EXT_EN > 0)
    OSIdleCtrRun  = 0L;
    OSIdleCtrMax  = 0L;
    OSStatRdy     = FALSE;                                       /* Statistic task is not ready              */
#endif
    OSCtxSwCtr    = 0;                                           /* Clear the context switch counter         */
    OSRdyGrp      = 0x00;                                        /* Clear the ready list                     */
    prdytbl       = &OSRdyTbl[0];
    for (i = 0; i < OS_RDY_TBL_SIZE; i++) {
        *prdytbl++ = 0x00;
    }

    OSPrioCur     = 0;
    OSPrioHighRdy = 0;
    OSTCBHighRdy  = (OS_TCB *)0;                                 /* TCB Initialization                       */
    OSTCBCur      = (OS_TCB *)0;
    OSTCBList     = (OS_TCB *)0;
    for (i = 0; i < (OS_LOWEST_PRIO + 1); i++) {                 /* Clear the priority table                 */
        OSTCBPrioTbl[i] = (OS_TCB *)0;
    }
    ptcb1 = &OSTCBTbl[0];
    ptcb2 = &OSTCBTbl[1];
    for (i = 0; i < (OS_MAX_TASKS + OS_N_SYS_TASKS - 1); i++) {  /* Init. list of free TCBs                  */
        ptcb1->OSTCBNext = ptcb2;
        ptcb1++;
        ptcb2++;
    }
    ptcb1->OSTCBNext = (OS_TCB *)0;                              /* Last OS_TCB                              */
    OSTCBFreeList    = &OSTCBTbl[0];

#if (OS_EVENT_EN > 0) && (OS_MAX_EVENTS > 0)
    #if OS_MAX_EVENTS == 1                                       
    OSEventFreeList              = &OSEventTbl[0];               /* Only have ONE event control block        */
    OSEventFreeList->OSEventType = OS_EVENT_TYPE_UNUSED;
    OSEventFreeList->OSEventPtr  = (OS_EVENT *)0;
    #else
    pevent1 = &OSEventTbl[0];
    pevent2 = &OSEventTbl[1];
    for (i = 0; i < (OS_MAX_EVENTS - 1); i++) {                  /* Init. list of free EVENT control blocks  */
        pevent1->OSEventType = OS_EVENT_TYPE_UNUSED;
        pevent1->OSEventPtr  = pevent2;
        pevent1++;
        pevent2++;
    }
    pevent1->OSEventType = OS_EVENT_TYPE_UNUSED;
    pevent1->OSEventPtr  = (OS_EVENT *)0;
    OSEventFreeList      = &OSEventTbl[0];
    #endif
#endif

#if (OS_VERSION >= 251) && (OS_FLAG_EN > 0) && (OS_MAX_FLAGS > 0)
    OS_FlagInit();                                               /* Initialize the event flag structures     */
#endif

#if (OS_Q_EN > 0) && (OS_MAX_QS > 0)
    OS_QInit();                                                  /* Initialize the message queue structures  */
#endif

#if (OS_MEM_EN > 0) && (OS_MAX_MEM_PART > 0)
    OS_MemInit();                                                /* Initialize the memory manager            */
#endif

    /* ------------------------------------- CREATION OF 'IDLE' TASK --------------------------------------- */
#if OS_TASK_CREATE_EXT_EN > 0
    #if OS_STK_GROWTH == 1
    (void)OSTaskCreateExt(OS_TaskIdle,
                          (void *)0,                                 /* No arguments passed to OS_TaskIdle() */
                          &OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE - 1], /* Set Top-Of-Stack                     */
                          OS_IDLE_PRIO,                              /* Lowest priority level                */
                          OS_TASK_IDLE_ID,
                          &OSTaskIdleStk[0],                         /* Set Bottom-Of-Stack                  */
                          OS_TASK_IDLE_STK_SIZE,
                          (void *)0,                                 /* No TCB extension                     */
                          OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);/* Enable stack checking + clear stack  */
    #else
    (void)OSTaskCreateExt(OS_TaskIdle,
                          (void *)0,                                 /* No arguments passed to OS_TaskIdle() */
                          &OSTaskIdleStk[0],                         /* Set Top-Of-Stack                     */
                          OS_IDLE_PRIO,                              /* Lowest priority level                */
                          OS_TASK_IDLE_ID,
                          &OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE - 1], /* Set Bottom-Of-Stack                  */
                          OS_TASK_IDLE_STK_SIZE,
                          (void *)0,                                 /* No TCB extension                     */
                          OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);/* Enable stack checking + clear stack  */
    #endif
#else
    #if OS_STK_GROWTH == 1
    (void)OSTaskCreate(OS_TaskIdle,
                       (void *)0,
                       &OSTaskIdleStk[OS_TASK_IDLE_STK_SIZE - 1],
                       OS_IDLE_PRIO);
    #else
    (void)OSTaskCreate(OS_TaskIdle,
                       (void *)0,
                       &OSTaskIdleStk[0],
                       OS_IDLE_PRIO);
    #endif
#endif

    /* ------------------------------- CREATION OF 'STATISTIC' TASK ---------------------------------- */
#if OS_TASK_STAT_EN > 0
    #if OS_TASK_CREATE_EXT_EN > 0
        #if OS_STK_GROWTH == 1
        (void)OSTaskCreateExt(OS_TaskStat,
                              (void *)0,                                   /* No args passed to OS_TaskStat()*/
                              &OSTaskStatStk[OS_TASK_STAT_STK_SIZE - 1],   /* Set Top-Of-Stack               */
                              OS_STAT_PRIO,                                /* One higher than the idle task  */
                              OS_TASK_STAT_ID,
                              &OSTaskStatStk[0],                           /* Set Bottom-Of-Stack            */
                              OS_TASK_STAT_STK_SIZE,
                              (void *)0,                                   /* No TCB extension               */
                              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  /* Enable stack checking + clear  */
        #else
        (void)OSTaskCreateExt(OS_TaskStat,
                              (void *)0,                                   /* No args passed to OS_TaskStat()*/
                              &OSTaskStatStk[0],                           /* Set Top-Of-Stack               */
                              OS_STAT_PRIO,                                /* One higher than the idle task  */
                              OS_TASK_STAT_ID,
                              &OSTaskStatStk[OS_TASK_STAT_STK_SIZE - 1],   /* Set Bottom-Of-Stack            */
                              OS_TASK_STAT_STK_SIZE,
                              (void *)0,                                   /* No TCB extension               */
                              OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);  /* Enable stack checking + clear  */
        #endif
    #else
        #if OS_STK_GROWTH == 1
        (void)OSTaskCreate(OS_TaskStat,
                           (void *)0,                                      /* No args passed to OS_TaskStat()*/
                           &OSTaskStatStk[OS_TASK_STAT_STK_SIZE - 1],      /* Set Top-Of-Stack               */
                           OS_STAT_PRIO);                                  /* One higher than the idle task  */
        #else
        (void)OSTaskCreate(OS_TaskStat,
                           (void *)0,                                      /* No args passed to OS_TaskStat()*/
                           &OSTaskStatStk[0],                              /* Set Top-Of-Stack               */
                           OS_STAT_PRIO);                                  /* One higher than the idle task  */
        #endif
    #endif
#endif

#if OS_VERSION >= 204
    OSInitHookEnd();                                                       /* Call port specific init. code  */
#endif
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                              ENTER ISR
*
* Description: This function is used to notify uC/OS-II that you are about to service an interrupt
*              service routine (ISR).  This allows uC/OS-II to keep track of interrupt nesting and thus
*              only perform rescheduling at the last nested ISR.
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) Your ISR can directly increment OSIntNesting without calling this function because
*                 OSIntNesting has been declared 'global'.  You MUST, however, be sure that the increment
*                 is performed 'indivisibly' by your processor to ensure proper access to this critical
*                 resource.
*              2) You MUST still call OSIntExit() even though you increment OSIntNesting directly.
*              3) You MUST invoke OSIntEnter() and OSIntExit() in pair.  In other words, for every call
*                 to OSIntEnter() at the beginning of the ISR you MUST have a call to OSIntExit() at the
*                 end of the ISR.
*********************************************************************************************************
*/

void  OSIntEnter (void)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
    OS_ENTER_CRITICAL();
    if (OSIntNesting < 255) {
        OSIntNesting++;                          /* Increment ISR nesting level                        */
    }
    OS_EXIT_CRITICAL();
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                               EXIT ISR
*
* Description: This function is used to notify uC/OS-II that you have completed serviving an ISR.  When
*              the last nested ISR has completed, uC/OS-II will call the scheduler to determine whether
*              a new, high-priority task, is ready to run.
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) You MUST invoke OSIntEnter() and OSIntExit() in pair.  In other words, for every call
*                 to OSIntEnter() at the beginning of the ISR you MUST have a call to OSIntExit() at the
*                 end of the ISR.
*              2) Rescheduling is prevented when the scheduler is locked (see OSSchedLock())
*********************************************************************************************************
*/

void  OSIntExit (void)
{
#if OS_CRITICAL_METHOD == 3                            /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr;
#endif
    
    
    OS_ENTER_CRITICAL();
    if (OSIntNesting > 0) {                            /* Prevent OSIntNesting from wrapping           */
        OSIntNesting--;
    }
    if ((OSIntNesting == 0) && (OSLockNesting == 0)) { /* Reschedule only if all ISRs complete ...     */
        OSIntExitY    = OSUnMapTbl[OSRdyGrp];          /* ... and not locked.                          */
        OSPrioHighRdy = (INT8U)((OSIntExitY << 3) + OSUnMapTbl[OSRdyTbl[OSIntExitY]]);
        if (OSPrioHighRdy != OSPrioCur) {              /* No Ctx Sw if current task is highest rdy     */
            OSTCBHighRdy  = OSTCBPrioTbl[OSPrioHighRdy];
            OSCtxSwCtr++;                              /* Keep track of the number of context switches */
            OSIntCtxSw();                              /* Perform interrupt level context switch       */
        }
    }
    OS_EXIT_CRITICAL();
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                          PREVENT SCHEDULING
*
* Description: This function is used to prevent rescheduling to take place.  This allows your application
*              to prevent context switches until you are ready to permit context switching.
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) You MUST invoke OSSchedLock() and OSSchedUnlock() in pair.  In other words, for every
*                 call to OSSchedLock() you MUST have a call to OSSchedUnlock().
*********************************************************************************************************
*/

#if OS_SCHED_LOCK_EN > 0
void  OSSchedLock (void)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
    if (OSRunning == TRUE) {                     /* Make sure multitasking is running                  */
        OS_ENTER_CRITICAL();
        if (OSLockNesting < 255) {               /* Prevent OSLockNesting from wrapping back to 0      */
            OSLockNesting++;                     /* Increment lock nesting level                       */
        }
        OS_EXIT_CRITICAL();
    }
}
#endif    

/*$PAGE*/
/*
*********************************************************************************************************
*                                          ENABLE SCHEDULING
*
* Description: This function is used to re-allow rescheduling.
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) You MUST invoke OSSchedLock() and OSSchedUnlock() in pair.  In other words, for every
*                 call to OSSchedLock() you MUST have a call to OSSchedUnlock().
*********************************************************************************************************
*/

#if OS_SCHED_LOCK_EN > 0
void  OSSchedUnlock (void)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
    if (OSRunning == TRUE) {                                   /* Make sure multitasking is running    */
        OS_ENTER_CRITICAL();
        if (OSLockNesting > 0) {                               /* Do not decrement if already 0        */
            OSLockNesting--;                                   /* Decrement lock nesting level         */
            if ((OSLockNesting == 0) && (OSIntNesting == 0)) { /* See if sched. enabled and not an ISR */
                OS_EXIT_CRITICAL();
                OS_Sched();                                    /* See if a HPT is ready                */
            } else {
                OS_EXIT_CRITICAL();
            }
        } else {
            OS_EXIT_CRITICAL();
        }
    }
}
#endif    

/*$PAGE*/
/*
*********************************************************************************************************
*                                          START MULTITASKING
*
* Description: This function is used to start the multitasking process which lets uC/OS-II manages the
*              task that you have created.  Before you can call OSStart(), you MUST have called OSInit()
*              and you MUST have created at least one task.
*
* Arguments  : none
*
* Returns    : none
*
* Note       : OSStartHighRdy() MUST:
*                 a) Call OSTaskSwHook() then,
*                 b) Set OSRunning to TRUE.
*********************************************************************************************************
*/

void  OSStart (void)
{
    INT8U y;
    INT8U x;


    if (OSRunning == FALSE) {
        y             = OSUnMapTbl[OSRdyGrp];        /* Find highest priority's task priority number   */
        x             = OSUnMapTbl[OSRdyTbl[y]];
        OSPrioHighRdy = (INT8U)((y << 3) + x);
        OSPrioCur     = OSPrioHighRdy;
        OSTCBHighRdy  = OSTCBPrioTbl[OSPrioHighRdy]; /* Point to highest priority task ready to run    */
        OSTCBCur      = OSTCBHighRdy;
        OSStartHighRdy();                            /* Execute target specific code to start task     */
    }
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                        STATISTICS INITIALIZATION
*
* Description: This function is called by your application to establish CPU usage by first determining
*              how high a 32-bit counter would count to in 1 second if no other tasks were to execute
*              during that time.  CPU usage is then determined by a low priority task which keeps track
*              of this 32-bit counter every second but this time, with other tasks running.  CPU usage is
*              determined by:
*
*                                             OSIdleCtr
*                 CPU Usage (%) = 100 * (1 - ------------)
*                                            OSIdleCtrMax
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

#if OS_TASK_STAT_EN > 0
void  OSStatInit (void)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
    OSTimeDly(2);                                /* Synchronize with clock tick                        */
    OS_ENTER_CRITICAL();
    OSIdleCtr    = 0L;                           /* Clear idle counter                                 */
    OS_EXIT_CRITICAL();
    OSTimeDly(OS_TICKS_PER_SEC);                 /* Determine MAX. idle counter value for 1 second     */
    OS_ENTER_CRITICAL();
    OSIdleCtrMax = OSIdleCtr;                    /* Store maximum idle counter count in 1 second       */
    OSStatRdy    = TRUE;
    OS_EXIT_CRITICAL();
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                         PROCESS SYSTEM TICK
*
* Description: This function is used to signal to uC/OS-II the occurrence of a 'system tick' (also known
*              as a 'clock tick').  This function should be called by the ticker ISR but, can also be
*              called by a high priority task.
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

void  OSTimeTick (void)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    OS_TCB    *ptcb;


    OSTimeTickHook();                                      /* Call user definable hook                 */
#if OS_TIME_GET_SET_EN > 0   
    OS_ENTER_CRITICAL();                                   /* Update the 32-bit tick counter           */
    OSTime++;
    OS_EXIT_CRITICAL();
#endif    
    ptcb = OSTCBList;                                      /* Point at first TCB in TCB list           */
    while (ptcb->OSTCBPrio != OS_IDLE_PRIO) {              /* Go through all TCBs in TCB list          */
        OS_ENTER_CRITICAL();
        if (ptcb->OSTCBDly != 0) {                         /* Delayed or waiting for event with TO     */
            if (--ptcb->OSTCBDly == 0) {                   /* Decrement nbr of ticks to end of delay   */
                if ((ptcb->OSTCBStat & OS_STAT_SUSPEND) == 0x00) {   /* Is task suspended?             */
                    OSRdyGrp               |= ptcb->OSTCBBitY; /* No,  Make task Rdy to Run (timed out)*/
                    OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
                } else {                                       /* Yes, Leave 1 tick to prevent ...     */
                    ptcb->OSTCBDly = 1;                        /* ... loosing the task when the ...    */
                }                                              /* ... suspension is removed.           */
            }
        }
        ptcb = ptcb->OSTCBNext;                                /* Point at next TCB in TCB list        */
        OS_EXIT_CRITICAL();
    }
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                             GET VERSION
*
* Description: This function is used to return the version number of uC/OS-II.  The returned value
*              corresponds to uC/OS-II's version number multiplied by 100.  In other words, version 2.00
*              would be returned as 200.
*
* Arguments  : none
*
* Returns    : the version number of uC/OS-II multiplied by 100.
*********************************************************************************************************
*/

INT16U  OSVersion (void)
{
    return (OS_VERSION);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                            DUMMY FUNCTION
*
* Description: This function doesn't do anything.  It is called by OSTaskDel().
*
* Arguments  : none
*
* Returns    : none
*********************************************************************************************************
*/

#if OS_TASK_DEL_EN > 0
void  OS_Dummy (void)
{
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                             MAKE TASK READY TO RUN BASED ON EVENT OCCURING
*
* Description: This function is called by other uC/OS-II services and is used to ready a task that was
*              waiting for an event to occur.
*
* Arguments  : pevent    is a pointer to the event control block corresponding to the event.
*
*              msg       is a pointer to a message.  This pointer is used by message oriented services
*                        such as MAILBOXEs and QUEUEs.  The pointer is not used when called by other
*                        service functions.
*
*              msk       is a mask that is used to clear the status byte of the TCB.  For example,
*                        OSSemPost() will pass OS_STAT_SEM, OSMboxPost() will pass OS_STAT_MBOX etc.
*
* Returns    : none
*
* Note       : This function is INTERNAL to uC/OS-II and your application should not call it.
*********************************************************************************************************
*/
#if OS_EVENT_EN > 0
INT8U  OS_EventTaskRdy (OS_EVENT *pevent, void *msg, INT8U msk)
{
    OS_TCB *ptcb;
    INT8U   x;
    INT8U   y;
    INT8U   bitx;
    INT8U   bity;
    INT8U   prio;


    y    = OSUnMapTbl[pevent->OSEventGrp];            /* Find highest prio. task waiting for message   */
    bity = OSMapTbl[y];
    x    = OSUnMapTbl[pevent->OSEventTbl[y]];
    bitx = OSMapTbl[x];
    prio = (INT8U)((y << 3) + x);                     /* Find priority of task getting the msg         */
    if ((pevent->OSEventTbl[y] &= ~bitx) == 0x00) {   /* Remove this task from the waiting list        */
        pevent->OSEventGrp &= ~bity;                  /* Clr group bit if this was only task pending   */
    }
    ptcb                 =  OSTCBPrioTbl[prio];       /* Point to this task's OS_TCB                   */
    ptcb->OSTCBDly       =  0;                        /* Prevent OSTimeTick() from readying task       */
    ptcb->OSTCBEventPtr  = (OS_EVENT *)0;             /* Unlink ECB from this task                     */
#if ((OS_Q_EN > 0) && (OS_MAX_QS > 0)) || (OS_MBOX_EN > 0)
    ptcb->OSTCBMsg       = msg;                       /* Send message directly to waiting task         */
#else
    msg                  = msg;                       /* Prevent compiler warning if not used          */
#endif
    ptcb->OSTCBStat     &= ~msk;                      /* Clear bit associated with event type          */
    if (ptcb->OSTCBStat == OS_STAT_RDY) {             /* See if task is ready (could be susp'd)        */
        OSRdyGrp        |=  bity;                     /* Put task in the ready to run list             */
        OSRdyTbl[y]     |=  bitx;
    }
    return (prio);
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                   MAKE TASK WAIT FOR EVENT TO OCCUR
*
* Description: This function is called by other uC/OS-II services to suspend a task because an event has
*              not occurred.
*
* Arguments  : pevent   is a pointer to the event control block for which the task will be waiting for.
*
* Returns    : none
*
* Note       : This function is INTERNAL to uC/OS-II and your application should not call it.
*********************************************************************************************************
*/
#if OS_EVENT_EN > 0
void  OS_EventTaskWait (OS_EVENT *pevent)
{
    OSTCBCur->OSTCBEventPtr = pevent;            /* Store pointer to event control block in TCB        */
    if ((OSRdyTbl[OSTCBCur->OSTCBY] &= ~OSTCBCur->OSTCBBitX) == 0x00) {   /* Task no longer ready      */
        OSRdyGrp &= ~OSTCBCur->OSTCBBitY;        /* Clear event grp bit if this was only task pending  */
    }
    pevent->OSEventTbl[OSTCBCur->OSTCBY] |= OSTCBCur->OSTCBBitX;          /* Put task in waiting list  */
    pevent->OSEventGrp                   |= OSTCBCur->OSTCBBitY;
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                              MAKE TASK READY TO RUN BASED ON EVENT TIMEOUT
*
* Description: This function is called by other uC/OS-II services to make a task ready to run because a
*              timeout occurred.
*
* Arguments  : pevent   is a pointer to the event control block which is readying a task.
*
* Returns    : none
*
* Note       : This function is INTERNAL to uC/OS-II and your application should not call it.
*********************************************************************************************************
*/
#if OS_EVENT_EN > 0
void  OS_EventTO (OS_EVENT *pevent)
{
    if ((pevent->OSEventTbl[OSTCBCur->OSTCBY] &= ~OSTCBCur->OSTCBBitX) == 0x00) {
        pevent->OSEventGrp &= ~OSTCBCur->OSTCBBitY;
    }
    OSTCBCur->OSTCBStat     = OS_STAT_RDY;       /* Set status to ready                                */
    OSTCBCur->OSTCBEventPtr = (OS_EVENT *)0;     /* No longer waiting for event                        */
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                 INITIALIZE EVENT CONTROL BLOCK'S WAIT LIST
*
* Description: This function is called by other uC/OS-II services to initialize the event wait list.
*
* Arguments  : pevent    is a pointer to the event control block allocated to the event.
*
* Returns    : none
*
* Note       : This function is INTERNAL to uC/OS-II and your application should not call it.
*********************************************************************************************************
*/
#if ((OS_Q_EN > 0) && (OS_MAX_QS > 0)) || (OS_MBOX_EN > 0) || (OS_SEM_EN > 0) || (OS_MUTEX_EN > 0)
void  OS_EventWaitListInit (OS_EVENT *pevent)
{
    INT8U  *ptbl;


    pevent->OSEventGrp = 0x00;                   /* No task waiting on event                           */
    ptbl               = &pevent->OSEventTbl[0];

#if OS_EVENT_TBL_SIZE > 0
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 1
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 2
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 3
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 4
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 5
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 6
    *ptbl++            = 0x00;
#endif

#if OS_EVENT_TBL_SIZE > 7
    *ptbl              = 0x00;
#endif
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                              SCHEDULER
*
* Description: This function is called by other uC/OS-II services to determine whether a new, high
*              priority task has been made ready to run.  This function is invoked by TASK level code
*              and is not used to reschedule tasks from ISRs (see OSIntExit() for ISR rescheduling).
*
* Arguments  : none
*
* Returns    : none
*
* Notes      : 1) This function is INTERNAL to uC/OS-II and your application should not call it.
*              2) Rescheduling is prevented when the scheduler is locked (see OSSchedLock())
*********************************************************************************************************
*/

void  OS_Sched (void)
{
#if OS_CRITICAL_METHOD == 3                            /* Allocate storage for CPU status register     */
    OS_CPU_SR  cpu_sr;
#endif    
    INT8U      y;


    OS_ENTER_CRITICAL();
    if ((OSIntNesting == 0) && (OSLockNesting == 0)) { /* Sched. only if all ISRs done & not locked    */
        y             = OSUnMapTbl[OSRdyGrp];          /* Get pointer to HPT ready to run              */
        OSPrioHighRdy = (INT8U)((y << 3) + OSUnMapTbl[OSRdyTbl[y]]);
        if (OSPrioHighRdy != OSPrioCur) {              /* No Ctx Sw if current task is highest rdy     */
            OSTCBHighRdy = OSTCBPrioTbl[OSPrioHighRdy];
            OSCtxSwCtr++;                              /* Increment context switch counter             */
            OS_TASK_SW();                              /* Perform a context switch                     */
        }
    }
    OS_EXIT_CRITICAL();
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                              IDLE TASK
*
* Description: This task is internal to uC/OS-II and executes whenever no other higher priority tasks
*              executes because they are ALL waiting for event(s) to occur.
*
* Arguments  : none
*
* Returns    : none
*
* Note(s)    : 1) OSTaskIdleHook() is called after the critical section to ensure that interrupts will be
*                 enabled for at least a few instructions.  On some processors (ex. Philips XA), enabling
*                 and then disabling interrupts didn't allow the processor enough time to have interrupts
*                 enabled before they were disabled again.  uC/OS-II would thus never recognize
*                 interrupts.
*              2) This hook has been added to allow you to do such things as STOP the CPU to conserve 
*                 power.
*********************************************************************************************************
*/

void  OS_TaskIdle (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
    pdata = pdata;                               /* Prevent compiler warning for not using 'pdata'     */
    for (;;) {
        OS_ENTER_CRITICAL();
        OSIdleCtr++;
        OS_EXIT_CRITICAL();
        OSTaskIdleHook();                        /* Call user definable HOOK                           */
    }
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                            STATISTICS TASK
*
* Description: This task is internal to uC/OS-II and is used to compute some statistics about the
*              multitasking environment.  Specifically, OS_TaskStat() computes the CPU usage.
*              CPU usage is determined by:
*
*                                          OSIdleCtr
*                 OSCPUUsage = 100 * (1 - ------------)     (units are in %)
*                                         OSIdleCtrMax
*
* Arguments  : pdata     this pointer is not used at this time.
*
* Returns    : none
*
* Notes      : 1) This task runs at a priority level higher than the idle task.  In fact, it runs at the
*                 next higher priority, OS_IDLE_PRIO-1.
*              2) You can disable this task by setting the configuration #define OS_TASK_STAT_EN to 0.
*              3) We delay for 5 seconds in the beginning to allow the system to reach steady state and
*                 have all other tasks created before we do statistics.  You MUST have at least a delay
*                 of 2 seconds to allow for the system to establish the maximum value for the idle
*                 counter.
*********************************************************************************************************
*/

#if OS_TASK_STAT_EN > 0
void  OS_TaskStat (void *pdata)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    INT32U     run;
    INT8S      usage;


    pdata = pdata;                               /* Prevent compiler warning for not using 'pdata'     */
    while (OSStatRdy == FALSE) {
        OSTimeDly(2 * OS_TICKS_PER_SEC);         /* Wait until statistic task is ready                 */
    }
    for (;;) {
        OS_ENTER_CRITICAL();
        OSIdleCtrRun = OSIdleCtr;                /* Obtain the of the idle counter for the past second */
        run          = OSIdleCtr;
        OSIdleCtr    = 0L;                       /* Reset the idle counter for the next second         */
        OS_EXIT_CRITICAL();
        if (OSIdleCtrMax > 0L) {
            usage = (INT8S)(100L - 100L * run / OSIdleCtrMax);
            if (usage >= 0) {                    /* Make sure we don't have a negative percentage      */
                OSCPUUsage = usage;
            } else {
                OSCPUUsage = 0;
            }
        } else {
            OSCPUUsage = 0;
        }
        OSTaskStatHook();                        /* Invoke user definable hook                         */
        OSTimeDly(OS_TICKS_PER_SEC);             /* Accumulate OSIdleCtr for the next second           */
    }
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                            INITIALIZE TCB
*
* Description: This function is internal to uC/OS-II and is used to initialize a Task Control Block when
*              a task is created (see OSTaskCreate() and OSTaskCreateExt()).
*
* Arguments  : prio          is the priority of the task being created
*
*              ptos          is a pointer to the task's top-of-stack assuming that the CPU registers
*                            have been placed on the stack.  Note that the top-of-stack corresponds to a
*                            'high' memory location is OS_STK_GROWTH is set to 1 and a 'low' memory
*                            location if OS_STK_GROWTH is set to 0.  Note that stack growth is CPU
*                            specific.
*
*              pbos          is a pointer to the bottom of stack.  A NULL pointer is passed if called by
*                            'OSTaskCreate()'.
*
*              id            is the task's ID (0..65535)
*
*              stk_size      is the size of the stack (in 'stack units').  If the stack units are INT8Us
*                            then, 'stk_size' contains the number of bytes for the stack.  If the stack
*                            units are INT32Us then, the stack contains '4 * stk_size' bytes.  The stack
*                            units are established by the #define constant OS_STK which is CPU
*                            specific.  'stk_size' is 0 if called by 'OSTaskCreate()'.
*
*              pext          is a pointer to a user supplied memory area that is used to extend the task
*                            control block.  This allows you to store the contents of floating-point
*                            registers, MMU registers or anything else you could find useful during a
*                            context switch.  You can even assign a name to each task and store this name
*                            in this TCB extension.  A NULL pointer is passed if called by OSTaskCreate().
*
*              opt           options as passed to 'OSTaskCreateExt()' or,
*                            0 if called from 'OSTaskCreate()'.
*
* Returns    : OS_NO_ERR         if the call was successful
*              OS_NO_MORE_TCB    if there are no more free TCBs to be allocated and thus, the task cannot
*                                be created.
*
* Note       : This function is INTERNAL to uC/OS-II and your application should not call it.
*********************************************************************************************************
*/

INT8U  OS_TCBInit (INT8U prio, OS_STK *ptos, OS_STK *pbos, INT16U id, INT32U stk_size, void *pext, INT16U opt)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    OS_TCB    *ptcb;


    OS_ENTER_CRITICAL();
    ptcb = OSTCBFreeList;                                  /* Get a free TCB from the free TCB list    */
    if (ptcb != (OS_TCB *)0) {
        OSTCBFreeList        = ptcb->OSTCBNext;            /* Update pointer to free TCB list          */
        OS_EXIT_CRITICAL();
        ptcb->OSTCBStkPtr    = ptos;                       /* Load Stack pointer in TCB                */
        ptcb->OSTCBPrio      = (INT8U)prio;                /* Load task priority into TCB              */
        ptcb->OSTCBStat      = OS_STAT_RDY;                /* Task is ready to run                     */
        ptcb->OSTCBDly       = 0;                          /* Task is not delayed                      */

#if OS_TASK_CREATE_EXT_EN > 0
        ptcb->OSTCBExtPtr    = pext;                       /* Store pointer to TCB extension           */
        ptcb->OSTCBStkSize   = stk_size;                   /* Store stack size                         */
        ptcb->OSTCBStkBottom = pbos;                       /* Store pointer to bottom of stack         */
        ptcb->OSTCBOpt       = opt;                        /* Store task options                       */
        ptcb->OSTCBId        = id;                         /* Store task ID                            */
#else
        pext                 = pext;                       /* Prevent compiler warning if not used     */
        stk_size             = stk_size;
        pbos                 = pbos;
        opt                  = opt;
        id                   = id;
#endif

#if OS_TASK_DEL_EN > 0
        ptcb->OSTCBDelReq    = OS_NO_ERR;
#endif

        ptcb->OSTCBY         = prio >> 3;                  /* Pre-compute X, Y, BitX and BitY          */
        ptcb->OSTCBBitY      = OSMapTbl[ptcb->OSTCBY];
        ptcb->OSTCBX         = prio & 0x07;
        ptcb->OSTCBBitX      = OSMapTbl[ptcb->OSTCBX];

#if OS_EVENT_EN > 0
        ptcb->OSTCBEventPtr  = (OS_EVENT *)0;              /* Task is not pending on an event          */
#endif

#if (OS_VERSION >= 251) && (OS_FLAG_EN > 0) && (OS_MAX_FLAGS > 0) && (OS_TASK_DEL_EN > 0)
        ptcb->OSTCBFlagNode  = (OS_FLAG_NODE *)0;          /* Task is not pending on an event flag     */
#endif

#if (OS_MBOX_EN > 0) || ((OS_Q_EN > 0) && (OS_MAX_QS > 0))
        ptcb->OSTCBMsg       = (void *)0;                  /* No message received                      */
#endif

#if OS_VERSION >= 204
        OSTCBInitHook(ptcb);
#endif

        OSTaskCreateHook(ptcb);                            /* Call user defined hook                   */
        
        OS_ENTER_CRITICAL();
        OSTCBPrioTbl[prio] = ptcb;
        ptcb->OSTCBNext    = OSTCBList;                    /* Link into TCB chain                      */
        ptcb->OSTCBPrev    = (OS_TCB *)0;
        if (OSTCBList != (OS_TCB *)0) {
            OSTCBList->OSTCBPrev = ptcb;
        }
        OSTCBList               = ptcb;
        OSRdyGrp               |= ptcb->OSTCBBitY;         /* Make task ready to run                   */
        OSRdyTbl[ptcb->OSTCBY] |= ptcb->OSTCBBitX;
        OS_EXIT_CRITICAL();
        return (OS_NO_ERR);
    }
    OS_EXIT_CRITICAL();
    return (OS_NO_MORE_TCB);
}
