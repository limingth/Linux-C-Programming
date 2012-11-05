/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h> 

//#define MAX(a, b)	((a)>(b))? (a):(b)
#define MAX(a, b)	(a>b)? a:b

int main( int argc, char * argv[] )
//int main( void )
{
	int j = 10;
	int _length = 100;

	for( i = 0; i < 10; i++)
	{


	}
	printf( "Hello, Cruel World! \n" );
	printf( "max(5, 7) = %d \n", MAX(0&2,1&1) );
//	printf( "max(5, 7) = %d \n", (5+5>1+7)? 5+5:1+7 );

	printf( "argc = %d \n", argc );
	printf( "argv[0] = %s \n", argv[0] );
	printf( "argv[1] = %s \n", argv[1] );
	printf( "argv[2] = %s \n", argv[2] );
	printf( "argv[3] = %s \n", argv[3] );
	printf( "argv[4] = %s \n", argv[4] );

	printf( " j = %d 0%o 0x%x \n", j, j, j );
	printf( " sizeof(int) = %d \n", sizeof(int) );
	printf( " sizeof(long) = %d \n", sizeof(long) );
	
	return 0;
}
