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

static void delay ( void )
{
	int i;
#ifdef EMBED
	for( i = 0 ; i < 100000 ; i++)
		;
#else
	for( i = 0 ; i < 100000000 ; i++)
		;
#endif

	return ;
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
		led_on(3);
		led_off(2);
		led_off(1);
	#ifndef EMBED
		led_show_status();
	#endif
		delay ();

		led_off(0);
		led_off(3);
		led_on(2);
		led_on(1);
	#ifndef EMBED
		led_show_status();
	#endif
		delay();
	}
}
