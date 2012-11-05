/*
 * calN.c   -- calculate how many N in a number
 * author:	li ming
 * date:   2006-09-18
 * version:   1.0
 */

#include <stdio.h>

#include "sum.h"

int main( void )
{
	int sum = 0;
	int begin = 1;
	int end = 100;
	int number = 9;

	sum = sum_cal_n(begin, end, number);

	printf( "from %d-%d, there is %d of %d \n", begin, end, sum, number );

	return 0;
}
