#include <stdio.h>

int main(void)
{
	int a[5] = {0,1,2,3,4};

	printf("value=%d\n", *((int *)(&a+1) - 1));
	return 0;
}
