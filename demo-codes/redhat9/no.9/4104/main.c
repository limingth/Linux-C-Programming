#include <stdio.h>

#include "led.h"
#include "dip.h"

int main( void )
{
	int value = 0;
	int num1 = 0;
	int num2 = 0;

	printf( "hello, world!\n" );
	
	led_set_value(0);
	while(1)
	{
		//if( int_get_status() == 1 )
		{	
			value = dip_get_value();
			led_set_value(value);
		}
	}
	return 0;
}
