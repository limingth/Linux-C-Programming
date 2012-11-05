#include <stdio.h>

#include "led_api.h"

static void delay ( void )
{
	int i;
	for( i = 0 ; i < 100000000 ; i++)
		;
	return ;
}

int led_init(void)
{
	led_open();
	return 0;
}

int led_on(int index)
{
	char s[4] = { -1, -1, -1, -1 };
	s[index] = 1;
	led_write( s, 4 );	
	return 0;
}

int led_off(int index)
{
	char s[4] = { -1, -1, -1, -1 };
	s[index] = 0;
	led_write( s, 4 );	
	return 0;
}

int led_running_horse(void)
{
	int i = 0;
	int index = 0;
	
	led_init();

	while(1)
	{
		led_off(0);
		led_off(1);
		led_off(2);
		led_off(3);

		index = i++ % 4;
		led_on(index);
	#ifndef EMBED
		led_show_status();
	#endif
		delay ();
	}
}

int led_two_blink(void)
{
	led_init();

	while(1)
	{
		led_on(0);
		led_on(1);
		led_off(2);
		led_off(3);
	#ifndef EMBED
		led_show_status();
	#endif
		delay ();

		led_off(0);
		led_off(1);
		led_on(2);
		led_on(3);
	#ifndef EMBED
		led_show_status();
	#endif
		delay();
	}
}
