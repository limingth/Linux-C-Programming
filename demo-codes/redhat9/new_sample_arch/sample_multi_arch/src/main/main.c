
#include <stdio.h>

#include "serial.h"
#include "net.h"

int main( void )
{
	printf( "<main.c> main running! \n" );
	
	serial_test();

	net_test();

	return 0;
}
