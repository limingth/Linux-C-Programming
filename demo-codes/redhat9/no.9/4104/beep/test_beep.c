
#include "beep.h"

int main(void)
{
	int i = 0;

	for(i = 0; i < 16; i++)
	{
		beep_n(i);
		sleep(1);
	}

	return;
}
