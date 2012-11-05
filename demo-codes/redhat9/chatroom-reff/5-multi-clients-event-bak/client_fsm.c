
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_fsm.h"
#include "client_view.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

/* different state-machine design as below */
#define EVENT_NUM		5
#define STATE_NUM		5

/* state machine transition table */
int client_fsm_transition_table[STATE_NUM][EVENT_NUM] = { 0 };

void (*client_fsm_action_table[STATE_NUM][EVENT_NUM])( void ) = { NULL };

/* client implement low-level functions */
int _state_transition( int state, int cond )
{
	return client_fsm_transition_table[state][cond];
}

typedef void (*PFI)( void );
PFI _transition_action( int state, int cond )
{
	return client_fsm_action_table[state][cond];
}

/* define new event */
static int client_new_event = 0;

/* init fsm */
int client_fsm_init( void )
{
	int i, j;

	/* init state machine table */
	for( i = 0; i < STATE_NUM; i++ )
		for( j = 0; j < EVENT_NUM; j++ )
		{
			client_fsm_transition_table[i][j] = i;
			client_fsm_action_table[i][j] = NULL;
		}
	
	/* state 0 -> state 0, 1, 2, 3 */
	client_fsm_transition_table[STATE_START][EVENT_K_NULL] = STATE_START;
	client_fsm_transition_table[STATE_START][EVENT_K_NEW] = STATE_USER_REGISTER;
	client_fsm_transition_table[STATE_START][EVENT_K_GUEST] = STATE_GUEST_LOGIN;
	client_fsm_transition_table[STATE_START][EVENT_K_STRING] = STATE_USER_LOGIN;
	
	/* state 1 -> state 4 */
	client_fsm_transition_table[STATE_USER_REGISTER][EVENT_K_STRING] = STATE_USER_REGISTER_NAME;

	/* state 4 -> state 5 */
	client_fsm_transition_table[STATE_USER_REGISTER_NAME][EVENT_N_REG_NAME_OK] = STATE_USER_REGISTER_PASSWORD;

	/* state 5 -> state 6 */
	client_fsm_transition_table[STATE_USER_REGISTER_PASSWORD][EVENT_N_REG_OK] = STATE_USER_REGISTER_OK;

	client_fsm_action_table[STATE_START][EVENT_K_NULL] = client_view_display_welcome;
	client_fsm_action_table[STATE_START][EVENT_K_NEW] = client_view_display_inputname;
	client_fsm_action_table[STATE_USER_REGISTER][EVENT_K_NEW] = client_view_display_notnew;
	client_fsm_action_table[STATE_USER_REGISTER][EVENT_K_GUEST] = client_view_display_notguest;
	client_fsm_action_table[STATE_USER_REGISTER][EVENT_K_STRING] = client_view_display_inputpassword;
	client_fsm_action_table[STATE_USER_REGISTER_NAME][EVENT_K_STRING] = client_view_display_reinputpassword;

	return 0;
}

/* translate an event to condition */
int client_fsm_event( int event )
{
	DPRINTF( "event:%d generated! \n", event );

	client_new_event = 1;
	
	fsm_set_condition( event );
	
	return event;
}

int client_fsm( void )
{
	int new_state = 0;

	void (*action)( void );

	new_state = fsm_state_transition();

	/* get user registed action pointer and call it */
	action = (void(*)(void)) _transition_action( fsm_get_state(), fsm_get_condition() );
	if( action != NULL )
		action();
		
	fsm_set_state( new_state );	

	switch( new_state )
	{
		case 1:
			client_reg_fsm();
			break;
		case 2:
			client_login_fsm();
			break;
		case 3:
			client_chat_fsm();
			break;
		case -1:
			exit(0);
	}
	
	return 0;
}

#if 0

#include "fsm.h"
int main( void )
{
	fd_set rfds;
	struct timeval tv;
	int retval;
	char buf[64];
	int i, j, n;

	client_fsm_init();

	while( state != -1 )
	{
		/* Watch stdin (fd 0) to see when it has input. */
		FD_ZERO( &rfds );
		FD_SET( 0, &rfds );

		/* Wait up to five seconds. */
		tv.tv_sec = 5;
		tv.tv_usec = 0;

		retval = select( 1, &rfds, NULL, NULL, &tv );
		if (retval)
		{
			/* FD_ISSET(0, &rfds) will be true. */
			if( FD_ISSET(0, &rfds) )
			{
				fgets( buf, 32, stdin );
				n = strlen( buf );
				buf[n-1] = '\0';
				printf( "get buf: %s (%d bytes) \n", buf, n-1 );

				if( strcmp(buf, EVENT_K_NEW_DATA) == 0 )
					FSM_EVENT( EVENT_K_NEW ); 
				else if( strcmp(buf, EVENT_K_GUEST_DATA) == 0 )
					FSM_EVENT( EVENT_K_GUEST ); 
				else
					FSM_EVENT( EVENT_K_INPUT_NAME );
			}
		}
		else
		{
			printf("No data within five seconds.\n");
			FSM_EVENT( EVENT_K_NULL ); 
		}

		FSM_TRANSITION();
	}
}
#endif
