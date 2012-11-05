
#include <stdio.h>

//#define DPRINT( fmt, args... )	
#define DPRINT( fmt, args... )	printf( fmt, ##args )

int get_char_type( char input )
{
	if( input == '+' || input == '-' )
		return 1;

	if( input >= '0' && input <= '9' )
		return 2;

	if( input == '.' )
		return 3;

	if( input == '\0' )
		return -1;

	return 4;
}

int number_count = 0;
char number_string[20][100];

int copy_to_number_string( char * src, int begin, int end )
{
	int i = 0;
	for( i = 0; i <= end - begin; i++ )
		number_string[number_count][i] = src[begin+i]; 

	number_string[number_count][i] = '\0'; 
	printf( ">>> number str[%d]: %s \n", number_count, number_string[number_count] );	
	printf( "----------------------------------------------- \n" );

	number_count++;
	return 0;
}

int find_number_string( char * src )
{
	/* 
	0: start
	1: get +/-	
	2: get 0-9
	3: get .
	4: get 0-9 after .
	0: end
	*/
	int state = 0;
	/* index of src char */
	int i = 0;
	/* input condition */
	int cond = 0;
	/* remember the begin position */
	int begin_pos = 0;

	int state_machine[][4] = {
					{ 1, 2, 0, 0 },
					{ 1, 2, 0, 0 },
					{ 1, 2, 3, 0 },
					{ 1, 4, 0, 0 },
					{ 1, 4, 0, 0 },
				};

	while( state != -1 )
	{
		cond = get_char_type( src[i] );

		if( state == 0 )
			begin_pos = i;

		if( state == 2 && (cond == 1 || cond == 4 || cond == -1) )
		{
			printf( "get a int muber string from %d to %d \n", begin_pos, i-1 );
			copy_to_number_string( src, begin_pos, i-1 );
		}
			
		if( state == 3 && (cond == 1 || cond == 3 || cond == 4 || cond == -1) )
		{
			printf( "get a int muber string from %d to %d \n", begin_pos, i-1 );
			copy_to_number_string( src, begin_pos, i-2 );
		}

		if( state == 4 && (cond == 1 || cond == 3 || cond == 4 || cond == -1) )
		{
			printf( "get a float muber string from %d to %d \n", begin_pos, i-1 );
			copy_to_number_string( src, begin_pos, i-1 );
		}

		if( (state == 1 || state == 2 || state == 3 || state == 4) && cond == 1 )
			begin_pos = i;

		if( cond == -1 )
			break;

		state = state_machine[state][cond-1];

		//printf( "input src[%d]:%c(0x%x) type is %d.  state:%d \n", i, src[i], src[i], cond, state );

		//getchar();

		i++;

	}
}

int main( void )
{
	char input_str[256];
	printf( "hello, final exam !\n" );
	
	printf( "please input your string: " );
	scanf( "%s", input_str );

	printf( "Your input string is <%s> \n", input_str );

	find_number_string( input_str );
	return 0;
}
