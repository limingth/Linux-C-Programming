#ifndef UART_H
#define UART_H

#define SYSCFG      0x03FF0000

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
 
#define	ULCR8bits	(3)
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
#define	USRDTR		(1 << 4)
#define	USRRxData      	(1 << 5) 
#define	USRTxHoldEmpty 	(1 << 6)
#define	USRTxEmpty     	(1 << 7)

 /* default baud rate value */
 
#define BAUD_9600	(162 << 4)

#define COM1_DEBUG	(1)
#define COM0_USER	(0)

// UART registers are on word aligned, D8

/* UART primitives */
#define GET_STATUS(p)	(*(volatile unsigned  *)((p) + USTAT))
#define RX_DATA(s)     	((s) & USRRxData)
#define GET_CHAR(p)	(*(volatile unsigned  *)((p) + URXBUF))
#define TX_READY(s)    	((s) & USRTxHoldEmpty)
#define PUT_CHAR(p,c)  	(*(unsigned  *)((p) + UTXBUF) = (unsigned )(c))

void uart_init( unsigned int UART_BASE, unsigned int baud );

int uart_putchar( unsigned int UART_BASE, char ch );

char uart_getchar( unsigned int UART_BASE );

int uart_test( void );

#endif

