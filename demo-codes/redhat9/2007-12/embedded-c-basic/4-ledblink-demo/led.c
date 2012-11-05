#include <stdio.h>

#include "led.h"

#ifndef EMBED
int led_status[4] = { 0 };

int led_show_status(void)
{
	int i = 0;
	
	printf( "\r" );
	for(i = 0; i < 4; i++)
	{
		if(led_status[i] == 1)
			printf("*");
		else
			printf("o");
	}
	fflush(stdout);
}
#endif

void led_init(void)
{
#ifdef EMBED
	R_IOPMOD |= LED_ALL;
#endif
	return;
}

void led_on(int index)
{
#ifdef EMBED
	switch (index)
	{
	case 0:				
		R_IOPDATA |= LED0;
		break;
	case 1:
		R_IOPDATA |= LED1;
		break;
	case 2:
		R_IOPDATA |= LED2;
		break;
	case 3:
		R_IOPDATA |= LED3;
		break;
	default:
		break;	
	}
#else
	led_status[index] = 1;
#endif

	return;
}

void led_off(int index)
{
#ifdef EMBED
	switch (index)
	{
	case 0:				
		R_IOPDATA &= ~LED0;
		break;
	case 1:
		R_IOPDATA &= ~LED1;
		break;
	case 2:
		R_IOPDATA &= ~LED2;
		break;
	case 3:
		R_IOPDATA &= ~LED3;
		break;
	default:
		break;	
	}
#else
	led_status[index] = 0;
#endif

	return;
}
