
#include "led.h"

int main(void)
{
	int i = 0;

	for(i = 0; i < 16; i++)
	{
		led_set_value(i);
		sleep(1);
	}

	return;
}
