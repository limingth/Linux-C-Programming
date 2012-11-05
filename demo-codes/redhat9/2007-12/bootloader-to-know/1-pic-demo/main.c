#include <stdio.h>

#include "add.h"
#include "sub.h"

int main(void)
{
	int x, y;

	x = add(1, 2);
	printf("x = %d \n", x);

	y = add(1, 2);
	printf("y = %d \n", y);
	 
	return 0;
}
