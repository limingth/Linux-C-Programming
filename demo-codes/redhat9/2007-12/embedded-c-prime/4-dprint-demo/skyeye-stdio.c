/*   
 *  skyeye_stdio.c  
 *  this file defines standard input/output on AT91X40 in SkyEye 
 *  for Atmel AT91 input/output
 *
 *  Bugs report:     li ming  ( lmcs00@mails.tsinghua.edu.cn )
 *  Last modified:   2003-02-02 
 *
 */

#include "skyeye-stdio.h"
#include "string.h"

#ifdef EMBED
#include "uart.h"

void skyeye_putc( char ch )
{
	uart_putchar( UART0_BASE, ch );
	return;	
}

char skyeye_getc(void)
{
	return uart_getchar( UART0_BASE );
}
#else
void skyeye_putc( char ch )
{
	putchar( ch );
	return;	
}

char skyeye_getc(void)
{
	return getchar();
}
#endif

char * skyeye_gets( char * s )
{
	char c;
	char * src = s;
	int count = 0;
	while(1)
	{
		c = skyeye_getc();
		
		if ( c == '\n' )
		{
			*src = '\0';
			skyeye_putc( c );
			break;
		}
		
		if ( c == '\b' )
		{
			if ( count <= 0 )
				continue;
			count--;
			src--;
			skyeye_putc( '\b' );
			skyeye_putc( ' ' );
			skyeye_putc( '\b' );
			continue;					
		}
		count++;
		*src++ = c;
		skyeye_putc( c );
	}
	
	return s;
}
