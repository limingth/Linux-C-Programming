/*
 *	led_driver.c -  led driver ( low-level )
 *	
 *	Author: 	yu feng <progeryf@gmail.com>
 *	Date:		2007-5-11
 */

#include "led_driver.h"

static char led_status[LED_NUM]; 

/* set led related gpio */
int led_open( void )
{
/* 
; hardware connection
; IO17 	IO04 	IO05 	IO06	(gpio)
; D6   	D7   	D8   	D9 	(led)
; so output value = 0x00020070 = (0b0000 0000  0000 0010  0000 0000  0111 0000)
*/
	unsigned int * IOPMOD = (unsigned int *)0x03FF5000;
	unsigned int * IOPDATA = (unsigned int *)0x03FF5008;
	int i;
	
	// set IOPMOD register mode bit to 1 = output ( refer to um_s3c4510b_rev1.pdf , page 12-2)
	*IOPMOD = *IOPMOD | 0x00020070;	
	
	// set IOPDATA register bit to 0 , initial led status = ALL_OFF
	*IOPDATA = *IOPDATA & (~0x00020070);
	
	for( i = 0; i < LED_NUM; i++ )
		led_status[i] = 0;	

	return 0;
}

int led_read( char * buf, int count )
{	
	int i = 0;
	
	// the count has exceeds the count of our board
	if( count > LED_NUM )
		return -1;
		
	for( i = 0; i < count; i++ )
		buf[i] = led_status[i];	
		
	return count;
}

int led_write( char * buf, int count )
{	
	int i = 0;
	unsigned int * IOPDATA = (unsigned int *)0x03FF5008;
	
	// the count has exceeds the count of our board	
	if( count > LED_NUM )
		return -1;
		
	for( i = 0; i < count; i++ )	
	{
		// save the write value for led_read
		led_status[i] = buf[i];

		// set IOPDATA register 
		switch (i)
		{
			case 0:				
				// buf[0] = IO 6
				*IOPDATA = buf[i]? (*IOPDATA | 0x00000040) : (*IOPDATA & (~0x00000040));
				break;
			case 1:
				// buf[1] = IO 5
				*IOPDATA = buf[i]? (*IOPDATA | 0x00000020) : (*IOPDATA & (~0x00000020));
				break;
			case 2:
				// buf[2] = IO 4
				*IOPDATA = buf[i]? (*IOPDATA | 0x00000010) : (*IOPDATA & (~0x00000010));
				break;
			case 3:
				// buf[3] = IO 17
				*IOPDATA = buf[i]? (*IOPDATA | 0x00020000) : (*IOPDATA & (~0x00020000));
				break;
			default:
				break;	
		}
	}	
	
	return count;
}

int led_ioctl( unsigned int cmd, unsigned long arg )
{
	// do nothing 	
	return 0;
}

int led_release( void )
{
	// do nothing 
	return 0;	
}
