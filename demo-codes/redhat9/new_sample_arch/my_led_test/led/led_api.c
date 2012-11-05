/*
 *	led_api.c   -   led api ( user-level )
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-3
 *	Copyleft:	http://www.lumit.org
 */
 
#include "led_driver.h"

#define LED_LIGHT_VALUE	1

#define LED_DARK_VALUE	0

#define LED_BLINK_DELAY	100	// about 1 second = 100

/* set led related gpio */
int led_init( void )
{
	led_open();
	return 0;
}

/* get 4 leds status to low-4-bits of hex value */
int led_get_value( void )
{
	char buf[LED_NUM];
	int value = 0x0;
	int i = 0;
	
	// read the led status from led driver
	led_read( buf, LED_NUM );
	
	for( i = 0; i < LED_NUM; i++ )
		value = value | (buf[i] << i);
		
	// return the led status in low-bits of value
	return value;
}

/* set hex value of low-4-bits to 4 leds */
int led_set_value( int value )
{
	char buf[LED_NUM];
	int i = 0;

	// set the i bit value to buf[i]
	for( i = 0; i < LED_NUM; i++ )
		buf[i] = (value & (1 << i)) ? 1 : 0 ;
	
	// write buf value back
	led_write( buf, LED_NUM );
	
	return 0;
}

int led_all_light( void )
{
	char buf[LED_NUM];
	int i;
		
	for( i = 0; i < LED_NUM; i++ )
		buf[i] = LED_LIGHT_VALUE;
	
	led_write( buf, LED_NUM );
	
	return 0;
}

int led_all_dark( void )
{	
	char buf[LED_NUM];
	int i;	
	
	for( i = 0; i < LED_NUM; i++ )
		buf[i] = LED_DARK_VALUE;
	
	led_write( buf, LED_NUM );
	
	return 0;
}

/* delay for about one second */
void led_delay( int time )	
{
	int i, j;

	for( i=0; i<time; i++ )
		for ( j=0; j<65536; j++ )
			;
}

int led_all_blink( void )
{
	led_all_dark();
	led_delay( LED_BLINK_DELAY );
	led_all_light();
	led_delay( LED_BLINK_DELAY );
	led_all_dark();	
	return 0;
}

int led_one_light( int position )
{	
	int led_value;
	
	// get current hex value from led driver
	led_value = led_get_value();
	
	// set the position bit to 1
	led_value |= (1 << position);
	
	// set current hex value to led driver
	led_set_value( led_value );
	
	return 0;
}

int led_one_dark( int position )
{
	int led_value;
	
	// get current hex value from led driver
	led_value = led_get_value();
	
	// set the position bit to 0
	led_value &= ~(1 << position);
	
	// set current hex value to led driver
	led_set_value( led_value );
	
	return 0;	
}

int led_one_blink( int position )
{
	led_one_dark( position );
	led_delay( LED_BLINK_DELAY );
	led_one_light( position );
	led_delay( LED_BLINK_DELAY );
	led_one_dark( position );	
	
	return 0;			
}

int led_test( void )
{	
	led_init();
	
	led_all_light();
	led_delay( 100 );
	
	led_all_dark();	
	led_delay( 100 );
	
	led_one_light( 0 );
	led_delay( 100 );
	
	led_one_light( 1 );
	led_delay( 100 );
	
	led_one_light( 2 );
	led_delay( 100 );
	
	led_one_light( 3 );
	led_delay( 100 );
	
	led_one_dark( 0 );
	led_delay( 100 );
	
	led_one_dark( 1 );
	led_delay( 100 );
	
	led_one_dark( 2 );
	led_delay( 100 );
	
	led_one_dark( 3 );
	led_delay( 100 );

	led_all_blink();
	
	led_one_blink( 0 );
	led_one_blink( 1 );
	led_one_blink( 2 );
	led_one_blink( 3 );
	
	return 0;
}
