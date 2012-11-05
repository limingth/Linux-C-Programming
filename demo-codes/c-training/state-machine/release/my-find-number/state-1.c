/*
 * state.c - using FSM to find number strings in buf
 *
 * Copyright (C) 2010	li ming <limingth@akaedu.org>
 *
 * find number string such as 123, 1, 03708 in "ab123+1-a03708"
 *
 */
#include <stdio.h>

#ifdef DEBUG
	#define DPRINT	printf
#else
	#define DPRINT	//
#endif

/* the string buffer to deal with */
char buf[1024] = "ad.+-0askjf908234jsda;dfj;asd907324kjw";
//char buf[1024] = "a1aa2i14f34";

/* the result number string buffer to save the result */
char numstr[32][64];

/*
 * get_input_type - get the input char TYPE ID
 *
 * 1: digit such as '0' - '9'
 * 2: character such as 'a','b','c'....
 * 3: '\0' - string end
 *
 */
int get_input_type( char ch )
{
	if ( ch >= '0' && ch <= '9' )
		return 1;

	if ( ch == '\0' )
		return 3;

	return 2;
}

/* input TYPE ID which is return from get_input_type */
int input;

/*
 * FSM state 
 *
 * 0: start state or restart state without digit 
 * 1: get a digit
 * -1: end state
 *
 * state transition:
 *        input
 * state	1	2	3
 *     0	1	0	-1
 *     1	1	0	-1
 *    -1	
 *
 */
int state;

/* record how many number string found */
int counter = 0;

int main(void)
{
	int i = 0;
	int pos = 0;

	printf( "please input a string : " );
	scanf( "%s", buf );
	printf( "your input string is: %s \n", buf );
	DPRINT( "%s\n", buf );

	i = 0;
	state = 0;
	while( state != -1 )
	{
		DPRINT( "(%d)", state );
		input = get_input_type( buf[i] );
		DPRINT( "%d ", input );

		switch( state )
		{	// state case
		case 0:
			switch( input )
			{	// input case
				case 1:
					state = 1;
					DPRINT( "first digit %d found! \n", buf[i]-'0' );
					numstr[counter][pos] = buf[i];
					pos++;
					break;
				case 2:
					state = 0;
					break;
				case 3:
					state = -1;
					break;
			}
			break;
		case 1:
			switch( input )
			{	// input case
				case 1:
					state = 1;
					DPRINT( "next digit %d found! \n", buf[i]-'0' );
					numstr[counter][pos] = buf[i];
					pos++;
					break;
				case 2:
					state = 0;
					numstr[counter][pos] = '\0';
					printf( "number %d found!  -> %s \n", counter+1, numstr[counter] );
					counter++;
					pos = 0;
					break;
				case 3:
					state = -1;
					numstr[counter][pos] = '\0';
					printf( "number %d found!  -> %s \n", counter+1, numstr[counter] );
					counter++;
					pos = 0;
					break;
			}
			break;
		case -1:
			break;
		}

		i++;
	}	
}
