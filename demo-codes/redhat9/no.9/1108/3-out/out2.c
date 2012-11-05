#include <stdio.h>
#include "pub.h"

int main(void)
{
	int i;
	int a[N];
	int left = N;
	int step = 0;
	int next;

	for (i = 0; i < N; i++)
		a[i] = (i+1)%N;

	printf( "out begin \n" );
	i = 0;
	while(left)
	{
		next = a[i];

		step++;

		if(step == 2)
		{
			a[i] = a[next];
			a[next] = 0;
			left--;
			//printf( "%d is out, %d is left \n", next+1, left );
			step = 0;
		}
		i = a[i];
	}
	printf( "%d is out, %d is left \n", next+1, left );

	return 0;
}
