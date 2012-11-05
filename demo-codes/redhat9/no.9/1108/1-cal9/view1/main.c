/*
 * calN.c   -- calculate how many N in a number
 * author:	li ming <limingth@akaedu.org>
 * date:   2006-09-18
 * version:   1.0
 */

#include <stdio.h>

int main( void )
{ 
	int rest = 0;		/* save the rest */
	int div = 0;		/* save the number after div */
	int counter = 0;	/* count the result for one number */
	int sum = 0;		/* count the sum result */
	int i = 0; 

	/* cal the number 9 from 1 to 100 */
	for( i = 1; i <= 10000; i++ )
	{
		div = i;

		/* loop div for 9 */
		while( div != 0 )
		{
			/* get the rest */
			rest = div % 10;
			div = div / 10;
			if( 9 == rest )
				counter++;
		}

		sum += counter;
		counter = 0;

	}
	printf( "from 0-100, there is %d of 9 \n", sum );

	return 0;
}
