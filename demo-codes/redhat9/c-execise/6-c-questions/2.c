/*
	calN.c   -- calculate how many N in a number
	author:	li ming
	date:   2006-09-18
	version:   1.0
*/

#include <stdio.h>

#define N 9
/* calculate how many 9 in int n, return x is the number of 9 */
int calN( int number )
{
	int rest = 0;
	int div = number;
	int counter = 0;
	
	while( div != 0 )
	{
		rest = div % 10;
		div = div / 10;
		if( N == rest )
			counter++;
	}

	return counter;
}

int main( void )
{
#if 0	
	int number = 0;
	int ret;
	printf( "please input a test number: " );
	scanf( "%d", &number );
	ret = calN( number );
	printf( "calN(%d) = %d \n", number, ret );
#endif

#if 1
	int i = 0, sum = 0;
	for( i=1; i<=10000; i++ )
	{
		if( i%3 == 0 && i%2 != 0 )
			if( i % 10 == 9 )
				sum += 1;
	}
	printf( "from 0-100, there is %d numbers ok. \n", sum);
#endif
	return 0;
}
