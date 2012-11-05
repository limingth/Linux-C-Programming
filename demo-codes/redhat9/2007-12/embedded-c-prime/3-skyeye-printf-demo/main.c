/*
 *	main.c    -     demo of how bootloader works
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

#include "uart.h"

int main( void )
{
	//uart_test();	

	skyeye_printf( "test=%d, 0x%x, %c \n", 100, 100, 100 );
	
	return 1;
}

