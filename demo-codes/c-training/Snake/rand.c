#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int my_rand()
{
	int n;
	srand(time(NULL));
	n =  rand()%24;
	if(n == 0)
	{n = n + 1;}

	return n;
}
