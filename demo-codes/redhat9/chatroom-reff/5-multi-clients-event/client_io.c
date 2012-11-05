#include <stdio.h>

extern int client_select_fd[];

void client_fsm_display_welcome( void )
{
	printf( "welcome to AKAE chatroom! \n" );
	printf( "Please input: (new, guest, yourname) " );
	fflush( stdout );
	return;
}


