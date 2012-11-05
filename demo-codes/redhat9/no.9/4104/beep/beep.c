
#include <stdio.h>
#include "beep.h"

int beep_n(int time)
{
#ifdef TARGET_PC
	/* pc simulate display */
	int i = 0;

	for(i = 0; i < time; i++)
	{
		printf("\a");
	}
#else
	/* add your led driver code here */

#endif
	
	return 0;
}

