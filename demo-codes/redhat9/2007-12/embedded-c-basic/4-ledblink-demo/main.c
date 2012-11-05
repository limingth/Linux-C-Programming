#include "led.h"

void delay ( void )
{
	int i;
	for( i = 0 ; i < 50000000 ; i++)
		;
	return ;
}

int main( void )
{
	int i = 0;
	int index = 0;
	
	led_init();

	while(1)
	{
		index = i++ % 4;
		led_on( index );
		led_off( (index+1)%4 );
		led_off( (index+2)%4 );
		led_off( (index+3)%4 );
	#ifndef EMBED
		led_show_status();
	#endif
		delay ();
	}

	return 0;
}
