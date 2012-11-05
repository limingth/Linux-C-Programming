/*
 * find9.c 
 *
 * to find how many 9 in 0-100
 *
 * Copyright (C) 2011 - 2021	Lee <liming@akaedu.org>
 */
#include <stdio.h>

/*
 * find() - to find how many digit in num
 * @num: 	an integer from 0 to 65535 
 * @digit:	a digit from 0 to 9
 *
 * return value: how many digit in num
 * 		 like find(1989, 9), return 2 
 * error code: 
 * -1: digit is not from 0-9, out of range 
 * -2: num is negtive 
 */
int find(int num, int digit)
{
	int counter = 0;

	/* to judge if digit is valid */
	if (digit > 9 || digit < 0)
		return -1;

	/* to judge if num is valid */
	if (num < 0)
		return -2;

	/* main loop to get last digit of num */
	do 
	{
		/* to judge if last digit is "digit" */
		if (num % 10 == digit)
			counter++;

		/* to get rid of the last digit */
		num /= 10;
	} while (num != 0); 	/* if loop is over */

	return counter;
}

int main(void)
{
	int i = 0;
	int begin = 0;		/* min num */
	int end = 100;		/* max num */
	int sum = 0;		/* return value */

	/* main loop */
	for (i = begin; i <= end; i++)
		sum += find(i, 9);
	
	printf("There is %d (9) total\n", sum);

	return 0;
}

