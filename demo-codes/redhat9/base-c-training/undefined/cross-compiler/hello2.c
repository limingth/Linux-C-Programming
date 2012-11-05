
#include <stdio.h>

int demo( void )
{
	int num = 0;
	return 1;

}

int main( void )
{
	int num = 0;

	printf( "hello, AKAEr! \n" );
	while(1)
	{
	printf( "please input a number: " );
	scanf( "%d", &num);
	printf( "Your number is %d \n", num );
	}
	
	demo();
	return 0;
}
