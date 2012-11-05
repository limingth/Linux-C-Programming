/*
 *	led_api.h  -   header file of led api
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-3
 *	Copyleft:	http://www.lumit.org
 */
 
#include "led_driver.h"

int led_init( void );

/* get 4 leds status to low-4-bits of hex value */
int led_get_value( void );

/* set hex value of low-4-bits to 4 leds */
int led_set_value( int value );

int led_all_light( void );

int led_all_dark( void );

int led_all_blink( void );

int led_one_light( int position );

int led_one_dark( int position );

int led_one_blink( int position );

int led_test( void );

