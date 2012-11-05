#include <stdio.h>
#define MAX 0
#include "a.h"
int myvar = 0;

int main( void )
{

	/* this is a comment */

#ifdef MAX 
	printf( "hello, world %d \n", MAX );
#endif

#if MAX == 5
	printf( "hello, world 4 %d \n", MAX );
#endif
	return 0;
}
