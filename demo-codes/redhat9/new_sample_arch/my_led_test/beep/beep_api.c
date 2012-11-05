/*
 *	beep_api.c   -  beep api ( user-level )
 *	
 *	Author: 	li ming <admin@lumit.org>
 *	Date:		2005-6-11
 *	Copyleft:	http://www.lumit.org
 */
 
#include "beep_api.h"

/* set beep related gpio */
int beep_init( void )
{
	beep_open();
	return 0;
}

// delay  1/1000000 s = 0.000001 s £¨ 1/1000 ∫¡√Î
static void beep_delay( int t )
{
	int i, j;

	for( i=0; i<10; i++ )
		for ( j=0; j<t; j++ )
			;
}

static int p_note[] = { P0, P1, P2, P3, P4, P5, P6, P7, P8, P9 };

// note: 1£¨2£¨3£¨4£¨5£¨6£¨7
// tone: µÕ∞À∂»£¨÷–∞À∂»£¨∏ﬂ∞À∂» [*1, *2, *4]
// div:  ∞À∑÷“Ù∑˚£ªÀƒ∑÷“Ù∑˚
int beep_note( int note, int tone, int div )
{	
	int freq = p_note[note] * tone;
	int loop = (1000*1000/(freq))/2;
	int count = (freq/div)*2 ;
	
	char beep_on = 1;
	char beep_off = 0;
		
	if( note > 9  || note < 0 )
		return -1;
	
	while( count-- )
	{
		beep_write( &beep_on, 1 );
		beep_delay( loop );
		beep_write( &beep_off, 1 );
		beep_delay( loop );
	}
	
	return 0;
}

/* –›÷π∑˚ */
void beep_rest( void )
{
	beep_delay( 40000 );
}

/* beep a song */
void beep_music( int psong[][3] )
{
	int i;
  
	for( i = 0; ; i++ ) 
	{
		if( psong[i][0] >= 1 )
			beep_note( psong[i][0], psong[i][1], psong[i][2] );
		if( psong[i][0] == 0 )
			beep_rest();
		if( psong[i][0] == -1 )
			break;
	}
}


static int test_note[][3] = 
{	
	{ 1, 2, 4 },	{ 0, 0, 0 },
	{ 2, 2, 4 },	{ 0, 0, 0 },
	{ 3, 2, 4 },	{ 0, 0, 0 },
	{ 4, 2, 4 }, 	{ 0, 0, 0 },
	{ 5, 2, 4 },	{ 0, 0, 0 },
	{ 6, 2, 4 },	{ 0, 0, 0 },
	{ 7, 2, 4 },	{ 0, 0, 0 },
	{ 1, 4, 4 }, 	{ 0, 0, 0 },
	{ 0, 0, 0 },	{ 0, 0, 0 },
	{ 1, 4, 4 },	{ 0, 0, 0 },
	{ 7, 2, 4 },	{ 0, 0, 0 },
	{ 6, 2, 4 },	{ 0, 0, 0 },
	{ 5, 2, 4 }, 	{ 0, 0, 0 },
	{ 4, 2, 4 },	{ 0, 0, 0 },
	{ 3, 2, 4 },	{ 0, 0, 0 },
	{ 2, 2, 4 },	{ 0, 0, 0 },
	{ 1, 2, 4 }, 	{ 0, 0, 0 },
	{ -1, 0, 0 }
};	

int beep_test( void )
{	
	beep_init();
	
	beep_music( test_note );
	
	return 0;
}
