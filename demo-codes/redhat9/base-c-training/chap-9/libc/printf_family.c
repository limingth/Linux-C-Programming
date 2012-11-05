/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int counter = 0;
char buf[64];

int main( int argc, char * argv[] )
{
	printf( "hello, Cruel World! \n" );
	
	fprintf( stdout, "to stdout: %d \n", counter++ );

	fprintf( stderr, "to stderr: %d \n", counter++ );
	fprintf( stderr, "to stderr: %d \n", counter++ );

	return 0;
	sprintf( buf, "test sprintf: %d \n", counter++ );
	printf( "%s", buf );
	return 0; 
}
