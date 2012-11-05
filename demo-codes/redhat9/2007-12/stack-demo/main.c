#include <stdio.h>

#include "add.h"
#include "sub.h"

int global = 100;
int global2 = 200;

int main(void)
{
	int local = 100;
	int local2 = 200;

	printf( "&global = 0x%x \n", &global );
	printf( "&global2 = 0x%x \n", &global2 );

	printf( "&local = 0x%x \n", &local );
	printf( "&local2 = 0x%x \n", &local2 );

#if 0
	int x, y;

	x = add(1, 2);
	printf("x = %d \n", x);

	y = sub(1, 2);
	printf("y = %d \n", y);
#endif
	 
	return 0;
}
