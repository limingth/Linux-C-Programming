/*
 *	beep_driver.c - beep driver ( low-level )
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-11
 *	Copyleft:	http://www.lumit.org
 */

#include "beep_driver.h"

/*  
; hardware connection
; PIO16	(gpio)
; 1  	(beep)
; so output value = 0x00010000 = (0b0000 0000  0000 0001  0000 0000  0000 0000)
*/

/* set beep related gpio */
int beep_open( void )
{
	// set gpio's direction: set IOPMOD register mode bit to 1 = output
	IOPMOD = IOPMOD | 0x00010000;

	return 0;
}

int beep_read( char * buf, int count )
{	
	// do nothing		
	return count;
}

/*
   if buf[i] == 0  BEEP_OFF
   else  BEEP_ON
*/   
int beep_write( char * buf, int count )
{	
	int i;
	
	for( i = 0; i < count; i++ )
	{
		if( buf[i] )
			IOPDATA = IOPDATA | 0x00010000;
		else
			IOPDATA = IOPDATA & (~0x00010000);		
	}
	
	return count;
}

int beep_ioctl( unsigned int cmd, unsigned long arg )
{
	// do nothing 	
	return 0;
}

int beep_release( void )
{
	// do nothing 
	return 0;	
}
