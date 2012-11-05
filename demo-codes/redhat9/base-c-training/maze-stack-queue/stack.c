#include <stdio.h>

char stack[512];

int top = 0;

void push( char ch )
{
	stack[top++] = ch;
}

char pop(void)
{
	return stack[--top];
}

int is_empty(void)
{
	return (top==0);
}

void print_stack(void)
{
	int i;
	
	printf( "-------\n" );
	for( i = top-1; i >= 0; i-- )
		printf( "%c \n", stack[i] );
	printf( "-------\n" );
	
	return;
}

int main(void)
{
	char c;
	push( 'a' );
	push( 'b' );
	push( 'c' );
	
	c =	pop();
	putchar( c );
	c = pop();
	putchar( c );

	push( '1' );
	push( '2' );

	print_stack();

	while( !is_empty() )
		putchar( pop() );

	putchar( '\n' );
	return 0;
}
