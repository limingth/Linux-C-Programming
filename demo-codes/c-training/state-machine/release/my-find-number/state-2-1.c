/*
 * state.c - using FSM to find (+/-)number strings in buf
 *
 * Copyright (C) 2010	li ming <limingth@akaedu.org>
 *
 * find number string such as 123, +1, -03708 in "ab123+1--03708"
 *
 */
#include <stdio.h>

#ifdef DEBUG
	#define DPRINT	printf
#else
	#define DPRINT	//
#endif

/* the string buffer to deal with */
//char buf[1024] = "ad.+-0askjf908234jsda;dfj;asd907324kjw";
char buf[1024] = "a+123--34aa34-+3";

/* the result number string buffer to save the result */
char numstr[32][64];

/*
 * get_input_type - get the input char TYPE ID
 *
 * 0: character such as 'a','b','c'....
 * 1: '+'/'-'
 * 2: digit such as '0' - '9'
 * 3: '\0' - string end
 *
 */
int get_input_type( char ch )
{
	if ( ch == '+' || ch == '-' )
		return 1;

	if ( ch >= '0' && ch <= '9' )
		return 2;

	if ( ch == '\0' )
		return 3;

	return 0;
}

/* input TYPE ID which is return from get_input_type */
int input;

/*
 * FSM state 
 *
 * 0: start state or restart state without digit 
 * 1: get a sign (+)
 * 2: get a digit (+1)
 * -1: end state
 *
 * state transition:
 *        input
 * state	0	1	2	3
 *     0	0	1	2	-1
 *     1	0	1	2	-1
 *     2	0	1	2	-1
 *    -1	.	.	.	.	
 *
 */
int state;

/* record how many number string found */
int counter = 0;

int i = 0;
int pos = 0;


void action_save(void)
{
	numstr[counter][pos] = buf[i];
	pos++;
}

void action_save2(void)
{
	pos--;
	action_save();
}

void action_found(void)
{
	numstr[counter][pos] = '\0';
	printf( "number %d found!  -> %s \n", counter+1, numstr[counter] );
	pos = 0;
	counter++;
}

void action_found_save(void)
{
	action_found();
	action_save();
}

int main(void)
{
//	printf( "please input a string : " );
//	scanf( "%s", buf );
	printf( "your input string is: %s \n", buf );
	DPRINT( "%s\n", buf );

	i = 0;
	state = 0;
	while( state != -1 )
	{
		DPRINT( "(%d)", state );
		input = get_input_type( buf[i] );
		DPRINT( "%d \n", input );

		switch( state )
		{	// state case
		case 0:
			switch( input )
			{	// input case
			case 0:	// "a"
				state = 0;
				break;
			case 1:	// "+"
				state = 1;
				DPRINT( "sign (%c) found! \n", buf[i] );
				action_save();
				break;
			case 2:	// "9"
				state = 2;
				DPRINT( "digit (%c) found! \n", buf[i] );
				action_save();
				break;
			case 3:	// "\0"
				state = -1;
				break;
			}
			break;
		case 1:
			switch( input )
			{	// input case
			case 0:	// "+a"
				state = 0;
				break;
			case 1:	// "+-"
				state = 1;
				DPRINT( "another sign %c found! \n", buf[i] );
				action_save2();
				break;
			case 2:	// "+9"
				state = 2;
				DPRINT( "first digit %c found! \n", buf[i] );
				action_save();
				break;
			case 3: // "+\0"
				state = -1;
				break;
			}
			break;
		case 2:
			switch( input )
			{	// input case
			case 0:	// "7a"
				state = 0;
				action_found();
				break;
			case 1:	// "7+"
				state = 1;
				action_found_save();
				break;
			case 2:	// "77"
				state = 2;
				DPRINT( "next digit %c found! \n", buf[i] );
				action_save();
				break;
			case 3:	// "7\0"
				state = -1;
				action_found();
				break;
			}
			break;
		case -1:
			break;
		}

		i++;
	}	
}
