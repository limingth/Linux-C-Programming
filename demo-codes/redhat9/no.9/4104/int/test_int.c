#include <stdio.h>
#include "int.h"

int main(void)
{
	int value = 0;

	while(1)
	{
		value = int_get_status();
		printf("get int status = 0x%x \n", value);
	}

	return 0;
}
