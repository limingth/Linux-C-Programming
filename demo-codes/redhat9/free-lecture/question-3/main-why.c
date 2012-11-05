#include <stdio.h>

int foo( int a )
{
	int b[1];

	a = 200;
	printf( "<foo> a = %d \n", a );
	
	printf( "<foo> b = 0x%x \n", b );
	b[8] = 200;
	return 0;
}


int main(void)
{
	int a;

	printf( "demo function parameter pass \n" );
	
	a = 100;
	printf( "<main> &a = 0x%x \n", &a );
	printf( "before <main> a = %d \n", a );
	foo( a );
	printf( "after <main> a = %d \n", a );
	
	return 0;
}
