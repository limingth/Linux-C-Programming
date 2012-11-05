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
	int i, j;
	printf( "hello, Cruel World! \n" );
	
	for( i = 0; i < 4; i++ )
	{
		for( j = 0; j < 10; j++ )
		{
			printf( "(i,j) = (%d,%d) \n", i, j );
			if( 2 == j )
			//	break;
				goto out;

		}
	}
out:
	return 0;
}
