#include <stdio.h>

#include "add.h"
#include "sub.h"

int test = 100;
int test2 = 200;

int main( void )
{
	int x, y;

	x = add( 1, 2 );
	printf( "x = %d \n", x );

	y = sub( 1, 2 );
	printf( "y = %d \n", y );
	
	return 0;
}
