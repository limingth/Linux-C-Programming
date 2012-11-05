/*
 *	led_driver.h -  header file of led driver
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-3
 *	Copyleft:	http://www.lumit.org
 */

#define LED_NUM		4

int led_open( void );

int led_read( char * buf, int count );

int led_write( char * buf, int count );

int led_ioctl( unsigned int cmd, unsigned long arg );

int led_release( void );

