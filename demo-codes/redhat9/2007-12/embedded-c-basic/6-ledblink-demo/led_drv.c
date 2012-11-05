#include <stdio.h>

#include "led_drv.h"

#ifndef EMBED
static unsigned char led_status[LED_NUM] = { 0 };

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

	return 0;
}
#endif

int led_open(void)
{
#ifdef EMBED
	R_IOPMOD |= LED_ALL;
	R_IOPDATA &= ~LED_ALL;
#else
	int i = 0;
	for( i = 0; i < LED_NUM; i++ )
		led_status[i] = 0;	
#endif
	return 0;
}

int led_read( char * buf, int count )
{	
#ifdef EMBED
	return -1;
#else
	int i = 0;
	
	// the count has exceeds the count of our board
	if( count > LED_NUM )
		return -1;
	
	for( i = 0; i < count; i++ )
		buf[i] = led_status[i];	
		
	return count;
#endif
}

int led_write( char * buf, int count )
{	
	int i = 0;
	
	// the count has exceeds the count of our board	
	if( count > LED_NUM )
		return -1;
		
	for( i = 0; i < count; i++ )	
	{
		if( buf[i] == 1 )
		{
#ifdef EMBED
			switch (i)
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
			led_status[i] = 1;
#endif
		}

		if( buf[i] == 0 )
	 	{
#ifdef EMBED
			switch (i)
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
			led_status[i] = 0;
#endif
		}
	}
	return count;
}

int led_release( void )
{
	// do nothing 
	return 0;	
}
