/*
 *	my_printf.c   - a sample printf 
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-11
 */
#include <stdarg.h>
#include "my_printf.h"
#include "uart.h"

/*
 * transfer the num to 10 or 16 and ouput it
 */

void output_int( unsigned int num, const int base )
{
	const char *digit = "0123456789ABCDEF";
	unsigned int buf[32];	
	int i = 0;	

	/*transfer the num to 10*/
	if (base == 10) 
	{	
		do
		{
			buf[i] = num % 10;
			num = num / 10;
			i++;
		} while ( num > 0 );
	}
	/*transfer the num to 16*/
	if (base == 16)
	{
		do
		{
			buf[i] = num % 16;
			num = num / 16;
			i++;
		} while ( num > 0 );
	}
	
	while ( --i >= 0 )	
	{
		uart_putchar( UART0_BASE, digit[ buf[i] ] );
	}
}

void my_printf( char *fmt_buf, ... )
{
	va_list unnamed_p;
	/* point to named argument */
	char *p, *sval;
	unsigned int value_i;

	/* unnamed_p point to first unnamed argument */
	va_start( unnamed_p, fmt_buf );

	for ( p=fmt_buf; *p; p++ )
	{
		if ( *p != '%' )
		{
			uart_putchar( UART0_BASE, *p );
			continue;
		}

		switch ( *++p )
		{
		case 'd':
			value_i = va_arg( unnamed_p, unsigned int );		
			output_int( value_i, 10 );
			break;

		case 's':
			for (sval = va_arg(unnamed_p, char*); *sval; sval++)
				uart_putchar( UART0_BASE, *sval );
			break;

		case 'x':
			value_i = va_arg( unnamed_p, unsigned int );		
			output_int( value_i, 16 );
			break;

		default:
			uart_putchar( UART0_BASE, *p );
			break;
		}
	}
	va_end( unnamed_p );
}

