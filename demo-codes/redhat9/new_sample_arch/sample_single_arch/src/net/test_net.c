
#include <stdio.h>
#include "net.h"
#include "serial.h"

int main( void )
{
	printf( "<test_net.c> main running! \n" );
	
	net_test();
	serial_test();

	return 0;
}
