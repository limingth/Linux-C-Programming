#include <stdio.h>

int foo( int a )
{
	int b[1];

	a = 200;
	
	b[8] = 123;
	return 0;
}

int main(void)
{
	int a;

	printf( "demo function parameter pass \n" );
	
	a = 100;
	printf( "before <main> a = %d \n", a );
	foo( a );
	printf( "after <main> a = %d \n", a );
	
	return 0;
}
