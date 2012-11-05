#include "led.h"

void delay ( void )
{
	int i;
	for( i = 0 ; i < 1000000 ; i++)
		;
	return ;
}

int main( void )
{
	while(1)
	{
		led_on();
		delay ();
		led_off();
		delay ();
	}

	return 0;
}
