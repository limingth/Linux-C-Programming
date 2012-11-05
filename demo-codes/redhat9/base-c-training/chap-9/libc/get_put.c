/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int main( int argc, char * argv[] )
{
	char a, b, c;
	char buf[128];

	printf( "hello, Cruel World! \n" );
	
	a = getchar();
	b = getc( stdin );
	printf( "get a = %c , b = %c \n", a, b );

	c = getchar();
	printf( "1: get c = %c(0x%x) \n", c, c );
	c = getchar();
	printf( "2: get c = %c(0x%x) \n", c, c );

	fgets( buf, 5, stdin );
	printf( "get buf str = %s \n", buf );

	c = ungetc( c, stdin );

	return 0; 
}
