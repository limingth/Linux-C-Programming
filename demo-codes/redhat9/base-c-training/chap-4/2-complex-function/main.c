/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

//#include "add.h"
#include "sub.h"

int main( int argc, char * argv[] )
{
	int ret;

	printf( "hello, Cruel World! \n" );
	
//	ret = g;

//	g = 100;
	ret = add( 100, 200 );	
	printf( "add = %d \n", ret );

	ret = sub( 100, 200 );	
	printf( "sub = %d \n", ret );

	return 0;
}
