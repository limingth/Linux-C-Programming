/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                        (c) Copyright 1992-1998, Jean J. Labrosse, Plantation, FL
*                                           All Rights Reserved
*
*                                                  V2.00
*
* File : uCOS_II.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#define  OS_GLOBALS                           /* Declare GLOBAL variables                              */
#include "includes.h"

#define  OS_CRITICAL_METHOD 	2

#define  OS_MASTER_FILE                       /* Prevent the following files from including includes.h */
#include "os_core.c"
#include "os_mbox.c"
#include "os_mem.c"
#include "os_q.c"
#include "os_sem.c"
#include "os_task.c"
#include "os_time.c"

