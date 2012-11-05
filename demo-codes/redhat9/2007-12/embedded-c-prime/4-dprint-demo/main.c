/*
 *	main.c    -     demo of how bootloader works
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

#include <stdio.h>

//#define sprint(expr)	skyeye_printf( "<skyeye> " #expr " = %d \n", expr )
#define sprint(expr)	printf( "main: " #expr " = %d \n", expr )

#ifdef DEBUG
#define dprint(expr)	printf( "<debug> " #expr " = %d \n", expr )
#else
#define dprint(expr)	
#endif

int main( void )
{
	int x = 100;	
	int y = 2;	

	dprint(x);
	dprint(y);

#if 0
	printf( "x = %d \n", x );
	printf( "y = %d \n", y );
	printf( "x + y = %d \n", x + y );
	printf( "x - y = %d \n", x - y );
	printf( "x * y = %d \n", x * y );
	printf( "x / y = %d \n", x / y );
#endif
//	return 0;

	sprint(x + y);
	sprint(x - y);
	sprint(x * y);
	sprint(x / y);
	sprint(x + 2 * y);

	return 0;
}

