#include <stdio.h>

int sum( int begin, int end )
{
	int i, sum = 0;

	for(i = begin; i <= end; i++ )
		sum += i;

	return sum;
}

int main( void )
{
	printf("sum(1, 100) = %d \n", sum(1, 100));

	return 0;
}
