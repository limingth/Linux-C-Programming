
#include <stdio.h>

#include "led_api.h"

int main( void )
{
	//led_running_horse();
	//led_two_blink();

	int counter = 0;

	while(1)
	{
		int i;
#ifdef EMBED
	//	get = int0_button_is_down();
		

#else
		char get;
		char buf[4];
		get = getc(stdin);

		counter++;
		//printf( "counter=%d \n", counter );
		led_off(0);
		led_off(1);
		led_off(2);
		led_off(3);
		
		for( i = 0; i < 4; i++ )
		{	
			buf[i] = ( (counter & 0xf) >> i ) & 0x1;
			if( buf[i] == 1 )
				led_on(i);
			else
				led_off(i);
			led_show_status();
		}	 
#endif
	}
	return 0;
}
