#include <stdio.h>

#include "client_fsm.h"

void client_view_display_welcome( void )
{
	printf( "welcome to AKAE chatroom! \n" );
	printf( "Please input: (new, guest, yourname) " );
	fflush( stdout );
	return;
}

void client_view_display_inputname( void )
{
	printf( "Your name: " );
	fflush( stdout );
	return;
}

void client_view_display_inputpassword( void )
{
	printf( "Your password: " );
	fflush( stdout );
	return;
}

void client_view_display_reinputpassword( void )
{
	printf( "Your password again: " );
	fflush( stdout );
	return;
}

void client_view_display_notnew( void )
{
	printf( "new is reserved by system! \n" );
	printf( "Please input yourname again:  " );
	fflush( stdout );

	return;
}

void client_view_display_notguest( void )
{
	printf( "guest is reserved by system! \n" );
	printf( "Please input yourname again:  " );
	fflush( stdout );

	return;
}

int client_view_parse( char * buf )
{
	if( fsm_get_state() == STATE_USER_REGISTER_NAME )
		client_fsm_event( EVENT_K_STRING ); 
		
	if( strcmp(buf, EVENT_K_NEW_DATA) == 0 )
		client_fsm_event( EVENT_K_NEW ); 
	else if( strcmp(buf, EVENT_K_GUEST_DATA) == 0 )
		client_fsm_event( EVENT_K_GUEST ); 
	else if( strcmp(buf, EVENT_K_NULL_DATA) == 0 )
		client_fsm_event( EVENT_K_NULL ); 
	else
		client_fsm_event( EVENT_K_STRING );
}
