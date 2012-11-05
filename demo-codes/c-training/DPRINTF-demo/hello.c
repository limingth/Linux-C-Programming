/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#define dprint( expr )	printf( "<main>" #expr "=%d \n", expr )
//#define dprint( expr )	printf( "<main>" #expr "=%d\n", expr )
//#define dprint( expr )	

//#define DPRINT( fmt, args... ) 	printf( fmt, ##args )
#define DPRINT( fmt, args... ) 	printf( fmt, ##args )
#define DPRINT2( fmt, args... ) 	printf( fmt, #args )

#define paste( front, back )	front##back
//#define paste2( front, back )	front#back

int main( int argc, char * argv[] )
{
	int i;
	int x = 100;
	int y = 2;	

	int name1 = 100;

	printf( "hello, Cruel World! \n" );
	
	dprint( x/y );
	dprint( x+y );
	dprint( x+y+2 );

	//return 0;

	printf( "name1 = %d \n", name1 );
	paste( name, 1 ) = 123;
	printf( "name1 = %d \n", name1 );

#if 0
	dprint( a );
	dprint( b );
	
	DPRINT( "a = %d b=%d ", 100, 200 );
	DPRINT2( "a = %d b=%d ", 100, 200 );
#endif
//	paste2( name, 2 );
	return 0; 
}
