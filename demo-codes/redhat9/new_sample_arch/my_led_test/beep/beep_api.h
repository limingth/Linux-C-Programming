/*
 *	beep_api.h  -   header file of beep api
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-11
 *	Copyleft:	http://www.lumit.org
 */
 
#include "beep_driver.h"

/* define DO RE MI ... ¶ÔÓ¦ÆµÂÊ hz */
#define		P0	200
#define		P1	264
#define		P2	297
#define		P3	330
#define		P4	352
#define		P5	396
#define		P6	440
#define		P7	495

#define		P8	560
#define		P9	660

  
/* init beep */
int beep_init( void );

/* beep a note */
int beep_note( int note, int tone, int div );

/* ÐÝÖ¹·û */
void beep_rest( void );

/* beep a song */
void beep_music( int psong[][3] );

/* test beep api */
int beep_test( void );
