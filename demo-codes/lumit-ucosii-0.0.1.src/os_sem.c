/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                          SEMAPHORE MANAGEMENT
*
*                          (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : OS_SEM.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

#if OS_SEM_EN > 0
/*
*********************************************************************************************************
*                                           ACCEPT SEMAPHORE
*
* Description: This function checks the semaphore to see if a resource is available or, if an event
*              occurred.  Unlike OSSemPend(), OSSemAccept() does not suspend the calling task if the
*              resource is not available or the event did not occur.
*
* Arguments  : pevent     is a pointer to the event control block
*
* Returns    : >  0       if the resource is available or the event did not occur the semaphore is
*                         decremented to obtain the resource.
*              == 0       if the resource is not available or the event did not occur or,
*                         if 'pevent' is a NULL pointer or,
*                         if you didn't pass a pointer to a semaphore
*********************************************************************************************************
*/

#if OS_SEM_ACCEPT_EN > 0
INT16U  OSSemAccept (OS_EVENT *pevent)
{
#if OS_CRITICAL_METHOD == 3                           /* Allocate storage for CPU status register      */
    OS_CPU_SR  cpu_sr;
#endif    
    INT16U     cnt;


#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                    /* Validate 'pevent'                             */
        return (0);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_SEM) {   /* Validate event block type                     */
        return (0);
    }
#endif
    OS_ENTER_CRITICAL();
    cnt = pevent->OSEventCnt;
    if (cnt > 0) {                                    /* See if resource is available                  */
        pevent->OSEventCnt--;                         /* Yes, decrement semaphore and notify caller    */
    }
    OS_EXIT_CRITICAL();
    return (cnt);                                     /* Return semaphore count                        */
}
#endif    

/*$PAGE*/
/*
*********************************************************************************************************
*                                           CREATE A SEMAPHORE
*
* Description: This function creates a semaphore.
*
* Arguments  : cnt           is the initial value for the semaphore.  If the value is 0, no resource is
*                            available (or no event has occurred).  You initialize the semaphore to a
*                            non-zero value to specify how many resources are available (e.g. if you have
*                            10 resources, you would initialize the semaphore to 10).
*
* Returns    : != (void *)0  is a pointer to the event control clock (OS_EVENT) associated with the
*                            created semaphore
*              == (void *)0  if no event control blocks were available
*********************************************************************************************************
*/

OS_EVENT  *OSSemCreate (INT16U cnt)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    OS_EVENT  *pevent;


    if (OSIntNesting > 0) {                                /* See if called from ISR ...               */
        return ((OS_EVENT *)0);                            /* ... can't CREATE from an ISR             */
    }
    OS_ENTER_CRITICAL();
    pevent = OSEventFreeList;                              /* Get next free event control block        */
    if (OSEventFreeList != (OS_EVENT *)0) {                /* See if pool of free ECB pool was empty   */
        OSEventFreeList = (OS_EVENT *)OSEventFreeList->OSEventPtr;
    }
    OS_EXIT_CRITICAL();
    if (pevent != (OS_EVENT *)0) {                         /* Get an event control block               */
        pevent->OSEventType = OS_EVENT_TYPE_SEM;
        pevent->OSEventCnt  = cnt;                         /* Set semaphore value                      */
        OS_EventWaitListInit(pevent);
    }
    return (pevent);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                         DELETE A SEMAPHORE
*
* Description: This function deletes a semaphore and readies all tasks pending on the semaphore.
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired
*                            semaphore.
*
*              opt           determines delete options as follows:
*                            opt == OS_DEL_NO_PEND   Delete semaphore ONLY if no task pending
*                            opt == OS_DEL_ALWAYS    Deletes the semaphore even if tasks are waiting.
*                                                    In this case, all the tasks pending will be readied.
*
*              err           is a pointer to an error code that can contain one of the following values:
*                            OS_NO_ERR               The call was successful and the semaphore was deleted
*                            OS_ERR_DEL_ISR          If you attempted to delete the semaphore from an ISR
*                            OS_ERR_INVALID_OPT      An invalid option was specified
*                            OS_ERR_TASK_WAITING     One or more tasks were waiting on the semaphore
*                            OS_ERR_EVENT_TYPE       If you didn't pass a pointer to a semaphore
*                            OS_ERR_PEVENT_NULL      If 'pevent' is a NULL pointer.
*
* Returns    : pevent        upon error
*              (OS_EVENT *)0 if the semaphore was successfully deleted.
*
* Note(s)    : 1) This function must be used with care.  Tasks that would normally expect the presence of
*                 the semaphore MUST check the return code of OSSemPend().
*              2) OSSemAccept() callers will not know that the intended semaphore has been deleted unless
*                 they check 'pevent' to see that it's a NULL pointer.
*              3) This call can potentially disable interrupts for a long time.  The interrupt disable
*                 time is directly proportional to the number of tasks waiting on the semaphore.
*              4) Because ALL tasks pending on the semaphore will be readied, you MUST be careful in
*                 applications where the semaphore is used for mutual exclusion because the resource(s)
*                 will no longer be guarded by the semaphore.
*********************************************************************************************************
*/

#if OS_SEM_DEL_EN > 0
OS_EVENT  *OSSemDel (OS_EVENT *pevent, INT8U opt, INT8U *err)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    BOOLEAN    tasks_waiting;


    if (OSIntNesting > 0) {                                /* See if called from ISR ...               */
        *err = OS_ERR_DEL_ISR;                             /* ... can't DELETE from an ISR             */
        return (pevent);
    }
#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                         /* Validate 'pevent'                        */
        *err = OS_ERR_PEVENT_NULL;
        return (pevent);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_SEM) {        /* Validate event block type                */
        *err = OS_ERR_EVENT_TYPE;
        return (pevent);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventGrp != 0x00) {                      /* See if any tasks waiting on semaphore    */
        tasks_waiting = TRUE;                              /* Yes                                      */
    } else {
        tasks_waiting = FALSE;                             /* No                                       */
    }
    switch (opt) {
        case OS_DEL_NO_PEND:                               /* Delete semaphore only if no task waiting */
             if (tasks_waiting == FALSE) {
                 pevent->OSEventType = OS_EVENT_TYPE_UNUSED;
                 pevent->OSEventPtr  = OSEventFreeList;    /* Return Event Control Block to free list  */
                 OSEventFreeList     = pevent;             /* Get next free event control block        */
                 OS_EXIT_CRITICAL();
                 *err = OS_NO_ERR;
                 return ((OS_EVENT *)0);                   /* Semaphore has been deleted               */
             } else {
                 OS_EXIT_CRITICAL();
                 *err = OS_ERR_TASK_WAITING;
                 return (pevent);
             }

        case OS_DEL_ALWAYS:                                /* Always delete the semaphore              */
             while (pevent->OSEventGrp != 0x00) {          /* Ready ALL tasks waiting for semaphore    */
                 OS_EventTaskRdy(pevent, (void *)0, OS_STAT_SEM);
             }
             pevent->OSEventType = OS_EVENT_TYPE_UNUSED;
             pevent->OSEventPtr  = OSEventFreeList;        /* Return Event Control Block to free list  */
             OSEventFreeList     = pevent;                 /* Get next free event control block        */
             OS_EXIT_CRITICAL();
             if (tasks_waiting == TRUE) {                  /* Reschedule only if task(s) were waiting  */
                 OS_Sched();                               /* Find highest priority task ready to run  */
             }
             *err = OS_NO_ERR;
             return ((OS_EVENT *)0);                       /* Semaphore has been deleted               */

        default:
             OS_EXIT_CRITICAL();
             *err = OS_ERR_INVALID_OPT;
             return (pevent);
    }
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                           PEND ON SEMAPHORE
*
* Description: This function waits for a semaphore.
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired
*                            semaphore.
*
*              timeout       is an optional timeout period (in clock ticks).  If non-zero, your task will
*                            wait for the resource up to the amount of time specified by this argument.
*                            If you specify 0, however, your task will wait forever at the specified
*                            semaphore or, until the resource becomes available (or the event occurs).
*
*              err           is a pointer to where an error message will be deposited.  Possible error
*                            messages are:
*
*                            OS_NO_ERR           The call was successful and your task owns the resource
*                                                or, the event you are waiting for occurred.
*                            OS_TIMEOUT          The semaphore was not received within the specified
*                                                timeout.
*                            OS_ERR_EVENT_TYPE   If you didn't pass a pointer to a semaphore.
*                            OS_ERR_PEND_ISR     If you called this function from an ISR and the result
*                                                would lead to a suspension.
*                            OS_ERR_PEVENT_NULL  If 'pevent' is a NULL pointer.
*
* Returns    : none
*********************************************************************************************************
*/

void  OSSemPend (OS_EVENT *pevent, INT16U timeout, INT8U *err)
{
#if OS_CRITICAL_METHOD == 3                           /* Allocate storage for CPU status register      */
    OS_CPU_SR  cpu_sr;
#endif    


    if (OSIntNesting > 0) {                           /* See if called from ISR ...                    */
        *err = OS_ERR_PEND_ISR;                       /* ... can't PEND from an ISR                    */
        return;
    }
#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                    /* Validate 'pevent'                             */
        *err = OS_ERR_PEVENT_NULL;
        return;
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_SEM) {   /* Validate event block type                     */
        *err = OS_ERR_EVENT_TYPE;
        return;
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventCnt > 0) {                     /* If sem. is positive, resource available ...   */
        pevent->OSEventCnt--;                         /* ... decrement semaphore only if positive.     */
        OS_EXIT_CRITICAL();
        *err = OS_NO_ERR;
        return;
    }
                                                      /* Otherwise, must wait until event occurs       */
    OSTCBCur->OSTCBStat |= OS_STAT_SEM;               /* Resource not available, pend on semaphore     */
    OSTCBCur->OSTCBDly   = timeout;                   /* Store pend timeout in TCB                     */
    OS_EventTaskWait(pevent);                         /* Suspend task until event or timeout occurs    */
    OS_EXIT_CRITICAL();
    OS_Sched();                                       /* Find next highest priority task ready         */
    OS_ENTER_CRITICAL();
    if (OSTCBCur->OSTCBStat & OS_STAT_SEM) {          /* Must have timed out if still waiting for event*/
        OS_EventTO(pevent);
        OS_EXIT_CRITICAL();
        *err = OS_TIMEOUT;                            /* Indicate that didn't get event within TO      */
        return;
    }
    OSTCBCur->OSTCBEventPtr = (OS_EVENT *)0;
    OS_EXIT_CRITICAL();
    *err = OS_NO_ERR;
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                         POST TO A SEMAPHORE
*
* Description: This function signals a semaphore
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired
*                            semaphore.
*
* Returns    : OS_NO_ERR           The call was successful and the semaphore was signaled.
*              OS_SEM_OVF          If the semaphore count exceeded its limit.  In other words, you have
*                                  signalled the semaphore more often than you waited on it with either
*                                  OSSemAccept() or OSSemPend().
*              OS_ERR_EVENT_TYPE   If you didn't pass a pointer to a semaphore
*              OS_ERR_PEVENT_NULL  If 'pevent' is a NULL pointer.
*********************************************************************************************************
*/

INT8U  OSSemPost (OS_EVENT *pevent)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;                               
#endif    


#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                         /* Validate 'pevent'                        */
        return (OS_ERR_PEVENT_NULL);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_SEM) {        /* Validate event block type                */
        return (OS_ERR_EVENT_TYPE);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventGrp != 0x00) {                      /* See if any task waiting for semaphore    */
        OS_EventTaskRdy(pevent, (void *)0, OS_STAT_SEM);   /* Ready highest prio task waiting on event */
        OS_EXIT_CRITICAL();
        OS_Sched();                                   /* Find highest priority task ready to run       */
        return (OS_NO_ERR);
    }
    if (pevent->OSEventCnt < 65535) {                 /* Make sure semaphore will not overflow         */
        pevent->OSEventCnt++;                         /* Increment semaphore count to register event   */
        OS_EXIT_CRITICAL();
        return (OS_NO_ERR);
    }
    OS_EXIT_CRITICAL();                               /* Semaphore value has reached its maximum       */
    return (OS_SEM_OVF);
}
/*
*********************************************************************************************************
*                                          QUERY A SEMAPHORE
*
* Description: This function obtains information about a semaphore
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired
*                            semaphore
*
*              pdata         is a pointer to a structure that will contain information about the
*                            semaphore.
*
* Returns    : OS_NO_ERR           The call was successful and the message was sent
*              OS_ERR_EVENT_TYPE   If you are attempting to obtain data from a non semaphore.
*              OS_ERR_PEVENT_NULL  If 'pevent' is a NULL pointer.
*********************************************************************************************************
*/

#if OS_SEM_QUERY_EN > 0
INT8U  OSSemQuery (OS_EVENT *pevent, OS_SEM_DATA *pdata)
{
#if OS_CRITICAL_METHOD == 3                                /* Allocate storage for CPU status register */
    OS_CPU_SR  cpu_sr;
#endif    
    INT8U     *psrc;
    INT8U     *pdest;


#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                         /* Validate 'pevent'                        */
        return (OS_ERR_PEVENT_NULL);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_SEM) {        /* Validate event block type                */
        return (OS_ERR_EVENT_TYPE);
    }
#endif
    OS_ENTER_CRITICAL();
    pdata->OSEventGrp = pevent->OSEventGrp;                /* Copy message mailbox wait list           */
    psrc              = &pevent->OSEventTbl[0];
    pdest             = &pdata->OSEventTbl[0];
#if OS_EVENT_TBL_SIZE > 0
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 1
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 2
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 3
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 4
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 5
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 6
    *pdest++          = *psrc++;
#endif

#if OS_EVENT_TBL_SIZE > 7
    *pdest            = *psrc;
#endif
    pdata->OSCnt      = pevent->OSEventCnt;                /* Get semaphore count                      */
    OS_EXIT_CRITICAL();
    return (OS_NO_ERR);
}
#endif                                                     /* OS_SEM_QUERY_EN                          */
#endif                                                     /* OS_SEM_EN                                */
