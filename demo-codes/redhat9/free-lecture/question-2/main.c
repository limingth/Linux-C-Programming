#include <stdio.h>

int foo( void )
{
	int a;

	printf( "<foo> a = %d \n", a );
	return 0;
}

int foo2( void )
{
	int a = 0;

	printf( "<foo2> a = %d \n", a );
	return 0;
}

int main(void)
{
	printf( "demo local variable address \n" );
	
	//foo();
	//foo2();
	
	foo2();
	foo();

	return 0;
}
