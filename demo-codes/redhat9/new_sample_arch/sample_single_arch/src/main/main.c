
#include <stdio.h>

#include "serial.h"
#include "net.h"
#include "chat.h"
#include "room.h"

int main( void )
{
	printf( "<main.c> main running! \n" );
	
	serial_test();

	net_test();
	net_test();

	chat_test();

	room_test();

	return 0;
}
