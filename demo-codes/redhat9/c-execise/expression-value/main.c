
#include <stdio.h>

#include "int_stack.h"
#include "char_stack.h"

/* define op prio */
int get_prio( char op )
{
	switch( op )
	{
		case '\0':
			return 0;
	
		case '+':
		case '-':
			return 1;

		case '*':
		case '/':
			return 2;
		
		case '^':
			return 3;
	}
	return -1;
}

/* get a number from char */
int get_number( char num )
{
	int ret;
	ret = num - '0';

	if( ret >= 0 && ret <= 9 )
		return ret;

	return -1;
}
		
char get_operator( char op )
{
	/* if op is right op, then return op */
	if( get_prio(op) >= 0 )
		return op;
	
	return -1;
}

int calc( int num1, int num2, char op )
{
	switch( op )
	{
		case '+':
			return num1+num2;
			
		case '-':
			return num1-num2;
		
		case '*':
			return num1*num2;

		case '/':
			return num1/num2;
	
		default:
			printf( "error op !\n" );
			break;
	}

	return -1;

}

int main( int argc, char * argv[] )
{
	int tmp;
	int i = 0;
	int num1;
	int num2;
	int new_num;
	char op;

	char * src; 

	char cur_op;
	char top_op;

	printf( "expression value demo begin !\n" );
#if 0
	push_int( 100 );

	push_int( 200 );

	tmp = pop_int();
	printf( "pop is %d \n", tmp );
	
	tmp = pop_int();
	printf( "pop is %d \n", tmp );
#endif
	if( argc > 1 )
		printf( "input expression string is %s \n", argv[1] );
	else 
		exit(0);

	src = argv[1];

	push_char( '\0');

	while( 1 )
	{
		printf( "src[%d] = %c \n", i, src[i] );	
get_num:		
		/* get a number */
		num1 = get_number( src[i] );
		if( num1 >= 0 )
			printf( "get a number : %d \n", num1 );	
		else
			break;

		/* push this number */
		printf( "push current int : %d \n", num1 );
		push_int( num1 );

		/* get the next op */
		i++;

		cur_op = get_operator( src[i] );
		if( cur_op > 0 )
			printf( "get a operator: %c \n", cur_op );	
		else if( cur_op == '\0' )
		{
			printf( "get a operator == 0: %c \n", cur_op );	
		}

cmp_op:
		top_op = get_top_char();
		printf( "get top stack operator: %c \n", top_op );	
		
		/* if current op > stack top op, then push current op */
		if( get_prio( cur_op ) > get_prio( top_op ) )
		{
			printf( "<push> push current op : %c \n", cur_op );
			push_char( cur_op );
			
			printf( "<push> push ok!\n" );
		}
		else
		{
			op = pop_char();
			num2 = pop_int();
			if( op == '\0' )
			{ 
				printf( "op == 0, last result = %d \n", num2 );
				exit( 0 );
			}

			num1 = pop_int();
			
			printf( "<calc> pop 2 num and 1 op, do calc: %d %c %d \n", num1, op, num2 );
			new_num = calc( num1, num2, op );
			printf( "get calc result: %d \n", new_num );
		
			/* push this new number */
			printf( "push new int : %d \n", new_num );
			push_int( new_num );

			goto cmp_op;
		}

		/* get the next op */
		i++;		
	} 

	return 0;
}
