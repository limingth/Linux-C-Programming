#include <stdio.h>

#include "led.h"

void led_on(void)
{
	R_IOPMOD |= LED_ALL;

	R_IOPDATA |= LED_ALL;

	return;
}

void led_off(void)
{
	R_IOPMOD |= LED_ALL;

	R_IOPDATA &= ~LED_ALL;

	return;
}
