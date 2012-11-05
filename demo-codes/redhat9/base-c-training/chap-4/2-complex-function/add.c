
#include "add.h"

int g = 0x12;

extern int g;

int add( int a, int b )
{
	printf( "g = %d \n", g );
	return a+b;
}
