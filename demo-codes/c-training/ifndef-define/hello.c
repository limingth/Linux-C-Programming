/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

//#include <stdio.h>

#include "add.h"
#include "sub.h"

int main( int argc, char * argv[] )
{
	counter = 123;

	printf( "hello, Cruel World! \n" );
	printf( "MAX = %d \n", MAX );
	printf( "counter = %d \n", counter );
	
	return 0;
}
