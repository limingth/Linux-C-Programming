/*
 *	main_entry.c -- the C_Entry for program
 *	
 *	Author: 	lumit-admin <admin@lumit.org>
 *	Date:		2004-8-26
 *	Copyright:	http://www.lumit.org
 */
 

#include <stdio.h>

//#define SYSCFG		(0x03ff0000)
#define UART0_BASE	(SYSCFG + 0xD000)
#define UART1_BASE 	(SYSCFG + 0xE000)

/*
 * Serial settings.......................
 */
	
#define	ULCON	0x00 
#define	UCON	0x04
#define	USTAT	0x08
#define	UTXBUF	0x0C
#define	URXBUF	0x10
#define	UBRDIV	0x14

/*
 * Line control register bits............
 */
 
#define	ULCR8bits		(3)
#define	ULCRS1StopBit	(0)
#define	ULCRNoParity	(0)

/*
 * UART Control Register bits............
 */
 
#define 	UCRRxM	(1)
#define 	UCRRxSI	(1 << 2)
#define 	UCRTxM	(1 << 3)
#define 	UCRLPB	(1 << 7)

/*
 * UART Status Register bits
 */
 
#define USROverrun     	(1 << 0)
#define	USRParity      	(1 << 1)
#define	USRFraming     	(1 << 2)
#define	USRBreak       	(1 << 3)
#define	USRDTR			(1 << 4)
#define	USRRxData      	(1 << 5) 
#define	USRTxHoldEmpty 	(1 << 6)
#define	USRTxEmpty     	(1 << 7)

#define GET_STATUS(p)	(*(volatile unsigned  *)((p) + USTAT))
#define RX_DATA(s)     	((s) & USRRxData)
#define GET_CHAR(p)		(*(volatile unsigned  *)((p) + URXBUF))
#define TX_READY(s)    	((s) & USRTxHoldEmpty)
#define PUT_CHAR(p,c)  	(*(unsigned  *)((p) + UTXBUF) = (unsigned )(c))

#define IRQVector	((unsigned *)0x18)

extern int  Angel_IRQ_Address;
extern void handler_irq(void);

#define SYSCFG	0x03ff0000

#define INTPND							((volatile unsigned *)(SYSCFG+0x4004))
#define INTMSK							((volatile unsigned *)(SYSCFG+0x4008))
#define INT_GLOBAL						(21)

#define TMOD				((volatile unsigned *)(SYSCFG+0x6000))  // timer mode register
#define TDATA0				((volatile unsigned *)(SYSCFG+0x6004))
#define TCNT0				((volatile unsigned *)(SYSCFG+0x600c))


int putchar_uart0(int ch)
{
    /* Place your implementation of fputc here     */
    /* e.g. write a character to a UART, or to the */
    /* debugger console with SWI WriteC            */   

	while ( TX_READY(GET_STATUS(UART0_BASE))==0);
	    PUT_CHAR(UART0_BASE, ch);
	    
   return ch;
}

struct __FILE { int handle;   /* Add whatever you need here */};
FILE __stdout;

int fputc(int ch, FILE *f)
{
    /* Place your implementation of fputc here     */
    /* e.g. write a character to a UART, or to the */
    /* debugger console with SWI WriteC            */   

   putchar_uart0( ch );
	    
   return ch;
}

int ferror(FILE *f)
{
    /* Your implementation of ferror */
    return EOF;
}


#define COUNTDOWN	0x01effff0;

static int counter = 0;


void  timer_irq (void) 
{ 

	// *TMOD	= 0; 
	*INTPND	= 1 << 10;
	*TDATA0	= COUNTDOWN; // reset interrupt

   // -- toggle the LED D4 to show timer interrupt...
   
    printf( "\r\n^ time-ticks = %d !\r\n", counter );
    counter = counter + 1;


	// -- re-enable interrupts ...

	// *TMOD	= 1;
	 *(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1 <<10) | (1<<0));
	 
} 

void install_irqhandler(void * isr)
{
	/* ARM irq exception vector addr is 0x00000018  */
	unsigned int * irq_vec_addr = ( unsigned int * ) 0x18;
	/* this is isr entry address, could be another address like 0x3c, 0x58... */
	unsigned int * isr_entry_addr = ( unsigned int * ) 0x38;

	unsigned int instruction;
	
	/* set the ISR entry at 0x38  */
	*isr_entry_addr = (unsigned int)isr;
	
	/* make an instruction: it is machine-code for "ldr  pc, [pc, #(38-18-8)]"  */
	instruction = ((unsigned int) isr_entry_addr  - (unsigned int)irq_vec_addr - 0x08) | 0xe59ff000;
	
	/* set this instruction at 0x18  */
	*irq_vec_addr = instruction;	
}

void timer_init (void)
{
  *TMOD		= 0;
  *INTPND 	= 0x00000000; 	// Clear pending interrupts .............
}

void timer_start (void)
{	
  *TDATA0		 = COUNTDOWN;	// reload CT .......................
  *TMOD 		|= 0x1;			// enable interval interrupt ...................
  
  *(volatile int*)INTMSK &= ~((1 << INT_GLOBAL) | (1 <<10) | (1<<0));
}

#include "includes.h"

void OSTickISR(void);


void Sleep(INT16U uSec)
{
	OSTimeDly((INT16U) (uSec));
}

void Task1(void * pParam)
{
	timer_init();
	timer_start();	
	while(1)	
	{
		printf( "@\r\n" );
		printf( "@\r\n" );
		printf( "@ task 1 running ... \r\n" );
		printf( "@    Q__Q    \r\n" );
		printf( "@   /____\\   \r\n" );
		printf( "@   \\____/   \r\n" );
		printf( "@    /\\/\\    \r\n" );
		printf( "@ __(\\\\//)__ \r\n" );
		printf( "@ >__/ww\\__< \r\n" );
		printf( "@\r\n" );
		printf( "@ go to sleep 5 time-ticks\r\n" );
		printf( "@\r\n" );
		printf( "@\r\n" );
		Sleep(5);
	}

}

/* Task2 print_user_input */
void Task2(void * pParam)
{
	while(1)	
	{
		printf( "+++ \r\n" );
		printf( "+++ \r\n" );
		printf( "+++  task 2 running ... \r\n" );
		printf( "+++  ¨q¦ä¦ä¦ä¨r \r\n" );
		printf( "+++ {/¡¡o¡¡o¡¡\\} \r\n" );
		printf( "+++  (¡¡(oo)¡¡) \r\n" );
		printf( "+++      ¦á \r\n" );
		printf( "+++ \r\n" );
		printf( "+++  go to sleep 2 time-ticks\r\n" );
		printf( "+++ \r\n" );
		printf( "+++ \r\n" );
		Sleep(2);
	}
}


#define	N_TASKS			3	// Number of tasks
#define	TASK_STK_SIZE	1024		// Stack size, in sizeof OS_STK, or int 32bit
OS_STK	TaskStk[N_TASKS][TASK_STK_SIZE];	// Tasks stacks

void C_Entry( void )
{
	int	task_1 = 0;
	int	task_2 = 1;
	counter = 0;
	printf( "start kernel ok!\r\n" );

	install_irqhandler( (void *)OSTickISR );
	
	OSInit();
	
	OSTaskCreate(Task1, &task_1, &TaskStk[0][TASK_STK_SIZE-1], 0);
	OSTaskCreate(Task2, &task_2, &TaskStk[1][TASK_STK_SIZE-1], 1);
	
	OSStart();
}
	
