/*
 *	main.c    -     demo of how bootloader works
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-5-24
 *	Copyleft:	http://www.lumit.org
 */

#include <stdio.h>

#define DEBUG_LEVEL 	0

#if DEBUG_LEVEL > 0
#define DPRINT(fmt, args...) 	printf(fmt, ##args)
#define LPRINT(level, fmt, args...)	if(level >= DEBUG_LEVEL) printf(fmt, ##args) 
#else
#define DPRINT(fmt, args...) 	
#define LPRINT(level, fmt, args...)	
#endif

int main( void )
{
	int x = 100;	
	int y = 2;	

	printf( "hello, Everyone!  Nice to meet you! \n" );

	LPRINT(1, "&x = 0x%x \n", &x);
	LPRINT(1, "&y = 0x%x \n", &y);

	LPRINT(2, "x = %d \n", x);
	LPRINT(2, "y = %d \n", y);

	DPRINT( "x + y = %d \n", x + y );
	DPRINT( "x - y = %d \n", x - y );
	DPRINT( "x * y = %d \n", x * y );
	DPRINT( "x / y = %d \n", x / y );

	return 0;
}

