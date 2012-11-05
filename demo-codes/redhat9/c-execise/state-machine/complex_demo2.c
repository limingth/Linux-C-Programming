
#include <stdio.h>


/* get input char type: 0-4 */
int get_char_type( char input )
{
	/* 
	input type :  0, 1, 2, 3, 4
		0: +/-
		1: 0-9
		2: .
		3: else like abc...
		4: '\0'
	*/
	if( input == '+' || input == '-' )
		return 0;

	if( input >= '0' && input <= '9' )
		return 1;

	if( input == '.' )
		return 2;

	if( input == '\0' )
		return 4;

	return 3;
}

char sub[64];

char * substr( char * src, int begin, int end )
{
	strncpy( sub, src+begin, end-begin+1 );

	sub[end-begin+1] = '\0';

	return sub;
}


char * src ;

/* 
0: start
1: get +/-	
2: get 0-9
3: get .
4: get 0-9 after .
0: end
*/
int state = 0, new_state;
/* index of src char */
int i = 0;
/* input condition */
int cond = 0;
/* remember the begin position */
int begin_pos = 0;
/* counter for number */
int counter = 0;


void action1( void )
{
	begin_pos = i;
}

void action2( void )
{
	printf( "%d--> get a int string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-1, substr(src, begin_pos, i-1) );
	begin_pos = i;
}

void action4( void )
{
	printf( "%d--> get a float string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-1, substr(src, begin_pos, i-1) );
	begin_pos = i;
}

void action3( void )
{
	printf( "%d--> get a int. string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-2, substr(src, begin_pos, i-2) );
	begin_pos = i;
}

/* state machine transition table */
int state_machine[][5] = {
				{ 1, 2, 0, 0, -1 },
				{ 1, 2, 0, 0, -1 },
				{ 1, 2, 3, 0, -1 },
				{ 1, 4, 0, 0, -1 },
				{ 1, 4, 0, 0, -1 },
			};

/* state machine transition action table */
void (*state_action[5][5])(void)  = {
				{ 0, 0, 0, 0, 0 },
				{ action1, 0, action1, action1, action1 },
				{ action2, 0, 0, action2, action2 },
				{ action3, 0, action3, action3, action3 },
				{ action4, 0, action4, action4, action4},
			};


int find_number_string( char * input_string )
{
	src = input_string;

	while( state != -1 )
	{
		cond = get_char_type( src[i] );

		/* remember the postion */
		if( state == 0 )
			begin_pos = i;

		/* run the state machine */
		new_state = state_machine[state][cond];

		printf( "state:%d ---input src[%d]:%c type:%d---> new_state:%d \n", state, i, src[i], cond, new_state );

		if( state_action[state][cond] )
			state_action[state][cond]();

#if 0
		if( new_state == 1 )
			begin_pos = i;

		if( state == 2 && (new_state==0 || new_state==1 || new_state==-1) )
		{
			printf( "%d--> get a int string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-1, substr(src, begin_pos, i-1) );
			begin_pos = i;
		}

		if( state == 4 && (new_state==0 || new_state==1 || new_state==-1) )
		{
			printf( "%d--> get a float string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-1, substr(src, begin_pos, i-1) );
			begin_pos = i;
		}

		if( state == 3 && (new_state==0 || new_state==1 || new_state==-1) )
		{
			printf( "%d--> get a int. string from src[%d] to src[%d]: %s \n", counter++, begin_pos, i-2, substr(src, begin_pos, i-2) );
			begin_pos = i;
		}
#endif

		/* set state = new_state */
		state = new_state;

		/* get the next char from src string */
		i++;

		//getchar();
	}
}

int main( int argc, char * argv[] )
{
	char * input_str;
	printf( "hello, complex state machine demo!\n" );
	
	if( argc > 1 )
		input_str = argv[1]; 

	printf( "Your input string is <%s> \n", input_str );

	find_number_string( input_str );
	return 0;
}
