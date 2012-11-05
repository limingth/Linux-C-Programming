/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*                                       MESSAGE MAILBOX MANAGEMENT
*
*                          (c) Copyright 1992-2001, Jean J. Labrosse, Weston, FL
*                                           All Rights Reserved
*
* File : OS_MBOX.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#ifndef  OS_MASTER_FILE
#include "includes.h"
#endif

#if OS_MBOX_EN > 0
/*
*********************************************************************************************************
*                                     ACCEPT MESSAGE FROM MAILBOX
*
* Description: This function checks the mailbox to see if a message is available.  Unlike OSMboxPend(),
*              OSMboxAccept() does not suspend the calling task if a message is not available.
*
* Arguments  : pevent        is a pointer to the event control block
*
* Returns    : != (void *)0  is the message in the mailbox if one is available.  The mailbox is cleared
*                            so the next time OSMboxAccept() is called, the mailbox will be empty.
*              == (void *)0  if the mailbox is empty or,
*                            if 'pevent' is a NULL pointer or,
*                            if you didn't pass the proper event pointer.
*********************************************************************************************************
*/

#if OS_MBOX_ACCEPT_EN > 0
void  *OSMboxAccept (OS_EVENT *pevent)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    void      *msg;


#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                        /* Validate 'pevent'                         */
        return ((void *)0);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {      /* Validate event block type                 */
        return ((void *)0);
    }
#endif
    OS_ENTER_CRITICAL();
    msg                = pevent->OSEventPtr;
    pevent->OSEventPtr = (void *)0;                       /* Clear the mailbox                         */
    OS_EXIT_CRITICAL();
    return (msg);                                         /* Return the message received (or NULL)     */
}
#endif
/*$PAGE*/
/*
*********************************************************************************************************
*                                        CREATE A MESSAGE MAILBOX
*
* Description: This function creates a message mailbox if free event control blocks are available.
*
* Arguments  : msg           is a pointer to a message that you wish to deposit in the mailbox.  If
*                            you set this value to the NULL pointer (i.e. (void *)0) then the mailbox
*                            will be considered empty.
*
* Returns    : != (OS_EVENT *)0  is a pointer to the event control clock (OS_EVENT) associated with the
*                                created mailbox
*              == (OS_EVENT *)0  if no event control blocks were available
*********************************************************************************************************
*/

OS_EVENT  *OSMboxCreate (void *msg)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    OS_EVENT  *pevent;


    if (OSIntNesting > 0) {                      /* See if called from ISR ...                         */
        return ((OS_EVENT *)0);                  /* ... can't CREATE from an ISR                       */
    }
    OS_ENTER_CRITICAL();
    pevent = OSEventFreeList;                    /* Get next free event control block                  */
    if (OSEventFreeList != (OS_EVENT *)0) {      /* See if pool of free ECB pool was empty             */
        OSEventFreeList = (OS_EVENT *)OSEventFreeList->OSEventPtr;
    }
    OS_EXIT_CRITICAL();
    if (pevent != (OS_EVENT *)0) {
        pevent->OSEventType = OS_EVENT_TYPE_MBOX;
        pevent->OSEventPtr  = msg;               /* Deposit message in event control block             */
        OS_EventWaitListInit(pevent);
    }
    return (pevent);                             /* Return pointer to event control block              */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                         DELETE A MAIBOX
*
* Description: This function deletes a mailbox and readies all tasks pending on the mailbox.
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired
*                            mailbox.
*
*              opt           determines delete options as follows:
*                            opt == OS_DEL_NO_PEND   Delete the mailbox ONLY if no task pending
*                            opt == OS_DEL_ALWAYS    Deletes the mailbox even if tasks are waiting.
*                                                    In this case, all the tasks pending will be readied.
*
*              err           is a pointer to an error code that can contain one of the following values:
*                            OS_NO_ERR               The call was successful and the mailbox was deleted
*                            OS_ERR_DEL_ISR          If you attempted to delete the mailbox from an ISR
*                            OS_ERR_INVALID_OPT      An invalid option was specified
*                            OS_ERR_TASK_WAITING     One or more tasks were waiting on the mailbox
*                            OS_ERR_EVENT_TYPE       If you didn't pass a pointer to a mailbox
*                            OS_ERR_PEVENT_NULL      If 'pevent' is a NULL pointer.
*
* Returns    : pevent        upon error
*              (OS_EVENT *)0 if the mailbox was successfully deleted.
*
* Note(s)    : 1) This function must be used with care.  Tasks that would normally expect the presence of
*                 the mailbox MUST check the return code of OSMboxPend().
*              2) OSMboxAccept() callers will not know that the intended mailbox has been deleted unless
*                 they check 'pevent' to see that it's a NULL pointer.
*              3) This call can potentially disable interrupts for a long time.  The interrupt disable
*                 time is directly proportional to the number of tasks waiting on the mailbox.
*              4) Because ALL tasks pending on the mailbox will be readied, you MUST be careful in
*                 applications where the mailbox is used for mutual exclusion because the resource(s)
*                 will no longer be guarded by the mailbox.
*********************************************************************************************************
*/

#if OS_MBOX_DEL_EN > 0
OS_EVENT  *OSMboxDel (OS_EVENT *pevent, INT8U opt, INT8U *err)
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
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {       /* Validate event block type                */
        *err = OS_ERR_EVENT_TYPE;
        return (pevent);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventGrp != 0x00) {                      /* See if any tasks waiting on mailbox      */
        tasks_waiting = TRUE;                              /* Yes                                      */
    } else {
        tasks_waiting = FALSE;                             /* No                                       */
    }
    switch (opt) {
        case OS_DEL_NO_PEND:                               /* Delete mailbox only if no task waiting   */
             if (tasks_waiting == FALSE) {
                 pevent->OSEventType = OS_EVENT_TYPE_UNUSED;
                 pevent->OSEventPtr  = OSEventFreeList;    /* Return Event Control Block to free list  */
                 OSEventFreeList     = pevent;             /* Get next free event control block        */
                 OS_EXIT_CRITICAL();
                 *err = OS_NO_ERR;
                 return ((OS_EVENT *)0);                   /* Mailbox has been deleted                 */
             } else {
                 OS_EXIT_CRITICAL();
                 *err = OS_ERR_TASK_WAITING;
                 return (pevent);
             }

        case OS_DEL_ALWAYS:                                /* Always delete the mailbox                */
             while (pevent->OSEventGrp != 0x00) {          /* Ready ALL tasks waiting for mailbox      */
                 OS_EventTaskRdy(pevent, (void *)0, OS_STAT_MBOX);
             }
             pevent->OSEventType = OS_EVENT_TYPE_UNUSED;
             pevent->OSEventPtr  = OSEventFreeList;        /* Return Event Control Block to free list  */
             OSEventFreeList     = pevent;                 /* Get next free event control block        */
             OS_EXIT_CRITICAL();
             if (tasks_waiting == TRUE) {                  /* Reschedule only if task(s) were waiting  */
                 OS_Sched();                               /* Find highest priority task ready to run  */
             }
             *err = OS_NO_ERR;
             return ((OS_EVENT *)0);                       /* Mailbox has been deleted                 */

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
*                                      PEND ON MAILBOX FOR A MESSAGE
*
* Description: This function waits for a message to be sent to a mailbox
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired mailbox
*
*              timeout       is an optional timeout period (in clock ticks).  If non-zero, your task will
*                            wait for a message to arrive at the mailbox up to the amount of time
*                            specified by this argument.  If you specify 0, however, your task will wait
*                            forever at the specified mailbox or, until a message arrives.
*
*              err           is a pointer to where an error message will be deposited.  Possible error
*                            messages are:
*
*                            OS_NO_ERR           The call was successful and your task received a
*                                                message.
*                            OS_TIMEOUT          A message was not received within the specified timeout
*                            OS_ERR_EVENT_TYPE   Invalid event type
*                            OS_ERR_PEND_ISR     If you called this function from an ISR and the result
*                                                would lead to a suspension.
*                            OS_ERR_PEVENT_NULL  If 'pevent' is a NULL pointer
*
* Returns    : != (void *)0  is a pointer to the message received
*              == (void *)0  if no message was received or,
*                            if 'pevent' is a NULL pointer or,
*                            if you didn't pass the proper pointer to the event control block.
*********************************************************************************************************
*/

void  *OSMboxPend (OS_EVENT *pevent, INT16U timeout, INT8U *err)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    void      *msg;


    if (OSIntNesting > 0) {                           /* See if called from ISR ...                    */
        *err = OS_ERR_PEND_ISR;                       /* ... can't PEND from an ISR                    */
        return ((void *)0);
    }
#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                    /* Validate 'pevent'                             */
        *err = OS_ERR_PEVENT_NULL;
        return ((void *)0);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {  /* Validate event block type                     */
        *err = OS_ERR_EVENT_TYPE;
        return ((void *)0);
    }
#endif
    OS_ENTER_CRITICAL();
    msg = pevent->OSEventPtr;
    if (msg != (void *)0) {                           /* See if there is already a message             */
        pevent->OSEventPtr = (void *)0;               /* Clear the mailbox                             */
        OS_EXIT_CRITICAL();
        *err = OS_NO_ERR;
        return (msg);                                 /* Return the message received (or NULL)         */
    }
    OSTCBCur->OSTCBStat |= OS_STAT_MBOX;              /* Message not available, task will pend         */
    OSTCBCur->OSTCBDly   = timeout;                   /* Load timeout in TCB                           */
    OS_EventTaskWait(pevent);                         /* Suspend task until event or timeout occurs    */
    OS_EXIT_CRITICAL();
    OS_Sched();                                       /* Find next highest priority task ready to run  */
    OS_ENTER_CRITICAL();
    msg = OSTCBCur->OSTCBMsg;
    if (msg != (void *)0) {                           /* See if we were given the message              */
        OSTCBCur->OSTCBMsg      = (void *)0;          /* Yes, clear message received                   */
        OSTCBCur->OSTCBStat     = OS_STAT_RDY;
        OSTCBCur->OSTCBEventPtr = (OS_EVENT *)0;      /* No longer waiting for event                   */
        OS_EXIT_CRITICAL();
        *err                    = OS_NO_ERR;
        return (msg);                                 /* Return the message received                   */
    }
    OS_EventTO(pevent);                               /* Timed out, Make task ready                    */
    OS_EXIT_CRITICAL();
    *err = OS_TIMEOUT;                                /* Indicate that a timeout occured               */
    return ((void *)0);                               /* Return a NULL message                         */
}
/*$PAGE*/
/*
*********************************************************************************************************
*                                       POST MESSAGE TO A MAILBOX
*
* Description: This function sends a message to a mailbox
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired mailbox
*
*              msg           is a pointer to the message to send.  You MUST NOT send a NULL pointer.
*
* Returns    : OS_NO_ERR            The call was successful and the message was sent
*              OS_MBOX_FULL         If the mailbox already contains a message.  You can can only send one
*                                   message at a time and thus, the message MUST be consumed before you
*                                   are allowed to send another one.
*              OS_ERR_EVENT_TYPE    If you are attempting to post to a non mailbox.
*              OS_ERR_PEVENT_NULL   If 'pevent' is a NULL pointer
*              OS_ERR_POST_NULL_PTR If you are attempting to post a NULL pointer
*********************************************************************************************************
*/

#if OS_MBOX_POST_EN > 0
INT8U  OSMboxPost (OS_EVENT *pevent, void *msg)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                    /* Validate 'pevent'                             */
        return (OS_ERR_PEVENT_NULL);
    }
    if (msg == (void *)0) {                           /* Make sure we are not posting a NULL pointer   */
        return (OS_ERR_POST_NULL_PTR);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {  /* Validate event block type                     */
        return (OS_ERR_EVENT_TYPE);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventGrp != 0x00) {                 /* See if any task pending on mailbox            */
        OS_EventTaskRdy(pevent, msg, OS_STAT_MBOX);   /* Ready highest priority task waiting on event  */
        OS_EXIT_CRITICAL();
        OS_Sched();                                   /* Find highest priority task ready to run       */
        return (OS_NO_ERR);
    }
    if (pevent->OSEventPtr != (void *)0) {            /* Make sure mailbox doesn't already have a msg  */
        OS_EXIT_CRITICAL();
        return (OS_MBOX_FULL);
    }
    pevent->OSEventPtr = msg;                         /* Place message in mailbox                      */
    OS_EXIT_CRITICAL();
    return (OS_NO_ERR);
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                       POST MESSAGE TO A MAILBOX
*
* Description: This function sends a message to a mailbox
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired mailbox
*
*              msg           is a pointer to the message to send.  You MUST NOT send a NULL pointer.
*
*              opt           determines the type of POST performed:
*                            OS_POST_OPT_NONE         POST to a single waiting task 
*                                                     (Identical to OSMboxPost())
*                            OS_POST_OPT_BROADCAST    POST to ALL tasks that are waiting on the mailbox
*
* Returns    : OS_NO_ERR            The call was successful and the message was sent
*              OS_MBOX_FULL         If the mailbox already contains a message.  You can can only send one
*                                   message at a time and thus, the message MUST be consumed before you
*                                   are allowed to send another one.
*              OS_ERR_EVENT_TYPE    If you are attempting to post to a non mailbox.
*              OS_ERR_PEVENT_NULL   If 'pevent' is a NULL pointer
*              OS_ERR_POST_NULL_PTR If you are attempting to post a NULL pointer
*
* Warning    : Interrupts can be disabled for a long time if you do a 'broadcast'.  In fact, the 
*              interrupt disable time is proportional to the number of tasks waiting on the mailbox.
*********************************************************************************************************
*/

#if OS_MBOX_POST_OPT_EN > 0
INT8U  OSMboxPostOpt (OS_EVENT *pevent, void *msg, INT8U opt)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    
    
#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                    /* Validate 'pevent'                             */
        return (OS_ERR_PEVENT_NULL);
    }
    if (msg == (void *)0) {                           /* Make sure we are not posting a NULL pointer   */
        return (OS_ERR_POST_NULL_PTR);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {  /* Validate event block type                     */
        return (OS_ERR_EVENT_TYPE);
    }
#endif
    OS_ENTER_CRITICAL();
    if (pevent->OSEventGrp != 0x00) {                 /* See if any task pending on mailbox            */
        if ((opt & OS_POST_OPT_BROADCAST) != 0x00) {  /* Do we need to post msg to ALL waiting tasks ? */
            while (pevent->OSEventGrp != 0x00) {      /* Yes, Post to ALL tasks waiting on mailbox     */           
                OS_EventTaskRdy(pevent, msg, OS_STAT_MBOX);    
            }
        } else {
            OS_EventTaskRdy(pevent, msg, OS_STAT_MBOX);    /* No,  Post to HPT waiting on mbox         */
        }
        OS_EXIT_CRITICAL();
        OS_Sched();                                   /* Find highest priority task ready to run       */
        return (OS_NO_ERR);
    }
    if (pevent->OSEventPtr != (void *)0) {            /* Make sure mailbox doesn't already have a msg  */
        OS_EXIT_CRITICAL();
        return (OS_MBOX_FULL);
    }
    pevent->OSEventPtr = msg;                         /* Place message in mailbox                      */
    OS_EXIT_CRITICAL();
    return (OS_NO_ERR);
}
#endif

/*$PAGE*/
/*
*********************************************************************************************************
*                                        QUERY A MESSAGE MAILBOX
*
* Description: This function obtains information about a message mailbox.
*
* Arguments  : pevent        is a pointer to the event control block associated with the desired mailbox
*
*              pdata         is a pointer to a structure that will contain information about the message
*                            mailbox.
*
* Returns    : OS_NO_ERR           The call was successful and the message was sent
*              OS_ERR_EVENT_TYPE   If you are attempting to obtain data from a non mailbox.
*              OS_ERR_PEVENT_NULL  If 'pevent' is a NULL pointer
*********************************************************************************************************
*/

#if OS_MBOX_QUERY_EN > 0
INT8U  OSMboxQuery (OS_EVENT *pevent, OS_MBOX_DATA *pdata)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr;
#endif    
    INT8U     *psrc;
    INT8U     *pdest;


#if OS_ARG_CHK_EN > 0
    if (pevent == (OS_EVENT *)0) {                         /* Validate 'pevent'                        */
        return (OS_ERR_PEVENT_NULL);
    }
    if (pevent->OSEventType != OS_EVENT_TYPE_MBOX) {       /* Validate event block type                */
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
    pdata->OSMsg = pevent->OSEventPtr;                     /* Get message from mailbox                 */
    OS_EXIT_CRITICAL();
    return (OS_NO_ERR);
}
#endif                                                     /* OS_MBOX_QUERY_EN                         */
#endif                                                     /* OS_MBOX_EN                               */
