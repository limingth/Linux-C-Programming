#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int my_rand(int bound)
{
	srand(time(NULL));

	return rand()%bound;
}
