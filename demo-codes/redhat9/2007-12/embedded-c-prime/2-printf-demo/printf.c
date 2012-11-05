/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#include <stdarg.h>

void myprintf( char * fmt, ... )
{
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;

	va_start( ap, fmt );

	for( p = fmt; *p; p++ )
	{
		if( *p != '%' )
		{
			putchar(*p);
			continue;
		}
		switch ( *++p )
		{
		case 'd':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for(sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		default:
			putchar(*p);
			break;
		}
	}
	va_end( ap );
}
