/*
 *	beep_driver.h - header file of beep driver
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-11
 *	Copyleft:	http://www.lumit.org
 */

#ifndef SYSCFG
#define SYSCFG      0x03FF0000
#endif
 
#ifndef IOPMOD
#define IOPMOD          (*((volatile unsigned *)(SYSCFG+0x5000)))
#endif

#ifndef IOPDATA
#define IOPDATA         (*((volatile unsigned *)(SYSCFG+0x5008)))
#endif
 
int beep_open( void );

int beep_read( char * buf, int count );

int beep_write( char * buf, int count );

int beep_ioctl( unsigned int cmd, unsigned long arg );

int beep_release( void );

