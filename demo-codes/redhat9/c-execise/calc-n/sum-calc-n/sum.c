/*
	calN.c   -- calculate how many N in a number
	author:	li ming
	date:   2006-09-18
	version:   1.0
*/

#include <stdio.h>

static int cal_n( int number, int n);

/* calculate how many 9 in int n, return x is the number of 9 */
static int cal_n( int number, int n)
{
	int rest = 0;
	int div = number;
	int counter = 0;
	
	while( div != 0 )
	{
		rest = div % 10;
		div = div / 10;
		if( n == rest )
			counter++;
	}

	return counter;
}

int sum_cal_n( int begin, int end, int number)
{
	int i = 0, sum = 0;

	for( i=begin; i<=end; i++ )
		sum += cal_n(i, number);

	return sum;
}
