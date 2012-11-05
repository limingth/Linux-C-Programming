#include <stdio.h>

/*
 * input: the char input
 * return value:   0:  0-9
 * 		   1:  abc....
 * 	  	  -1:  '\0'
 *
 */
int get_input_type( char input )
{

	/* get char 0-9 */
	if( input >= '0' && input <= '9' )
		return 0;

	/* get char '\0', string end */
	if( input == '\0' )
		return -1;

	/* else other char, return -1 */
	return 1;

}

int main( int argc, char * argv[] )
{
	/* the index of source string */
	int i = 0;

	/* input char 's condition type */
	int cond = 0;

	/* define the input char */
	char input;

	/* get the input char type */
	int input_type;
	
	/* define the state machine status */
	int state = 0;

	printf( "state machine demo begin ! \n" );
	
	/* check input argument */
	if( argc > 1 )
		printf( "input string is \n%s \n", argv[1] );

	/* state machine begin ! */
	state = 0;

	#define END  -100
	/* check the input char by char */
///	while( state != -100 )
	while( state != END )
	{
		/* get current input char */
		input = argv[1][i];
//		printf( "input char is %c \n", input );
//		printf( "%c", input );

		/* get input char type */
		input_type = get_input_type( input );
		//printf( "input char type is %d \n", input_type );
		//printf( "%d", input_type );

		printf( "state = %d \n", state );
		printf( "input char type is %d \n", input_type );
		switch( state )
		{
			case 0:
				switch ( input_type )
				{
					case 0: 
						state = 1;
						break;

					case 1: 
						//state = -1;
						#define E1  -1
						state = E1;
						printf( "\ne1: you input like <a>  \n" );
						goto error;
						break;
					case -1:
						#define END -100
//						state = -100;
						state = END; 
						printf( "end: no number string ! \n" );
				}
				break;
			case 1:
				switch ( input_type )
				{
					case 0: 
						state = 1;
						break;

					case 1: 
						state = -2;
						printf( "\ne2: you input like <9a>  \n" );
						goto error;
						break;
					case -1:
						state = -100;
						printf( "end: number string is ok! \n" );
				}
				break;
		}
		i++;
	}

	printf( "\n" );
	return 0;

error:
	printf( "error happen !\n" );
	return -1;
}
