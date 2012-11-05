/*
 *	uart.h    -     header file for uart driver
 *	
 *	Author: 	yu feng<progeryf@gmail.com>
 *	Date:		2007-5-28
 */

/**************************************************************
 * ROUTINES
 **************************************************************/
#ifndef SYSCFG
#define SYSCFG      0x03FF0000
#endif

#define UART0_BASE	(SYSCFG + 0xD000)
#define UART1_BASE 	(SYSCFG + 0xE000)

/* default baud rate value */ 
#define BAUD_9600	(162 << 4)

/* add 19200 for xmodem*/
#define BAUD_19200	(80 << 4)

#define BAUD_38400	(40 << 4)
#define BAUD_57600	(26 << 4)

/* add 115200 for download faster */
#define BAUD_115200	(13 << 4)
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
 * every bit see datasheet
 */
 
#define USROverrun     	(1 << 0)
#define	USRParity      	(1 << 1)
#define	USRFraming     	(1 << 2)
#define	USRBreak       	(1 << 3)
#define	USRDTR			(1 << 4)
#define	USRRxData      	(1 << 5) 
#define	USRTxHoldEmpty 	(1 << 6)
#define	USRTxEmpty     	(1 << 7)

#define COM1_DEBUG		(1)
#define COM0_USER		(0)

// UART registers are on word aligned, D8

/* UART primitives */
#define GET_STATUS(p)	(*(volatile unsigned  *)((p) + USTAT))
#define RX_DATA(s)     	((s) & USRRxData)
#define GET_CHAR(p)		(*(volatile unsigned  *)((p) + URXBUF))
#define TX_READY(s)    	((s) & USRTxHoldEmpty)
#define PUT_CHAR(p,c)  	(*(unsigned  *)((p) + UTXBUF) = (unsigned )(c))

void uart_init( unsigned int UART_BASE, unsigned int baud );
int uart_putchar( unsigned int UART_BASE, char ch );
int uart_getchar( unsigned int UART_BASE, char * ch );
int uart_test( void );
