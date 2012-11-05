#include <stdio.h>
#include "pub.h"

int main(void)
{
	int i;
	int a[N];
	int left = N;
	int step = 0;

	for (i = 0; i < N; i++)
		a[i] = 1;

	printf( "out begin \n" );
	i = 0;
	while(left)
	{
		if(a[i] == 1)	
			step++;

		if(step == 3)
		{
			a[i] = 0;
			left--;
	//		printf( "%d is out, %d is left \n", i+1, left );

			step = 0;
		}

		i++;

		if( i==N )
			i = 0;
	}

	printf( "%d is out, %d is left \n", i, left );
	return 0;
}
