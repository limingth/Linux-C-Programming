#include <stdio.h>

#include "led.h"

void led_on(void)
{
#ifdef EMBED
	R_IOPMOD |= LED_ALL;

	R_IOPDATA |= LED_ALL;
#else
	printf( "led_on \n" );
#endif

	return;
}

void led_off(void)
{
#ifdef EMBED
	R_IOPMOD |= LED_ALL;

	R_IOPDATA &= ~LED_ALL;
#else
	printf( "led_off \n" );
#endif

	return;
}
