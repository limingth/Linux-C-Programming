/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#include "mydef.h"

#define MAX	5
#define MIN	0

#define WELCOME 1 
//#undef WELCOME

char str[32] = "aabbccdd" ;
int myint = 0x11;

int main( int argc, char * argv[] )
{
	/* ccc */
#if WELCOME == 0
//#ifdef WELCOME 
	printf( "hello, /* ccc */ Cruel World! \n" );  /* ccc */ ; printf( "test\n" );
#else
	printf( "no welcome msg! \n" );
#endif
	if( argc > MIN && argc < MAX )
	{	printf( "argc is ok: %3d \n", A );
		printf( "argc is ok: %d \n", A );
	}
	/* ccc */
	else
		printf( "argc is error \n" );
		 
	return 16; 
}
