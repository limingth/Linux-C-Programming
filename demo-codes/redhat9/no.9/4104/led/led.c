
#include <stdio.h>
#include "led.h"

int led_set_value(int value)
{
#ifdef TARGET_PC
	/* pc simulate display */
	int i = 0;

	printf("\r");
	for(i = 3; i >= 0; i--)
	{
		/* judge if led[4-i] set-value is 1, from left to right */
		if(value & (1 << i))
			printf("1");
		else
			printf("0");
	}
	fflush(stdout);
#else
	/* add your led driver code here */

#endif
	
	return 0;
}

