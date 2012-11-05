/*
 *	uart.c    -     driver of uart 
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

#include "uart.h"

void uart_init( unsigned int UART_BASE, unsigned int baud )
{
   /* Disable interrupts  */
   *(volatile unsigned *) (UART_BASE + UCON) = 0;

   /* Set port for 8 bit, one stop, no parity  */
   *(volatile unsigned *) (UART_BASE + ULCON) = (ULCR8bits);

   /* Enable interrupt operation on UART */
   *(volatile unsigned *) (UART_BASE + UCON) = UCRRxM | UCRTxM;

   /* Set baud rate  */
   *(volatile unsigned *) (UART_BASE + UBRDIV) = baud;

}

int uart_putchar( unsigned int UART_BASE, char ch )
{
	/* read tx ready flag, when =1 break */
	while ( TX_READY(GET_STATUS(UART_BASE))==0)
		;
	
	PUT_CHAR(UART_BASE, ch);

	return ch;
}

char uart_getchar( unsigned int UART_BASE )
{
	char ch;

	/* read rx ready flag, when =1 break */
	while ( (RX_DATA(GET_STATUS(UART_BASE)))==0 ) 
		;		

	ch = GET_CHAR(UART_BASE);

	return ch;
}

/* a very simple uart driver test for echo function */
int uart_test( void )
{
	char ch ;
	
	uart_init( UART0_BASE, BAUD_9600 );
	
	while( 1 )
	{
		ch = uart_getchar( UART0_BASE );
		uart_putchar( UART0_BASE, ch );
	}
	
	return 0;
}

