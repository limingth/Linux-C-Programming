
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_fsm.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<client_fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

/* different state-machine design as below */
#define EVENT_NUM		5
#define STATE_NUM		5

/* state machine transition table */
int client_fsm_transition_table[STATE_NUM][EVENT_NUM] = { 0 };

void (*client_fsm_action_table[STATE_NUM][EVENT_NUM])( void ) = { NULL };

extern int client_select_fd[];

/* client implement low-level functions */
int client_state_transition( int state, int cond )
{
	return client_fsm_transition_table[state][cond];
}

typedef void (*PF_VV)( void );
PF_VV client_transition_action( int state, int cond )
{
	return client_fsm_action_table[state][cond];
}

void client_reg_fsm( void );
void client_fsm_display_welcome( void );

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
	
	/* install fsm hooker */
	fsm_init_install( client_state_transition, client_transition_action );	

	/* state 0 -> state 0, 1, 2, 3 */
	client_fsm_transition_table[S0_START][E0_K_NULL] = S0_START;
	client_fsm_transition_table[S0_START][E1_K_NEW] = S1_USER_REGISTER;
	client_fsm_transition_table[S0_START][E2_K_GUEST] = S2_GUEST_LOGIN;
	client_fsm_transition_table[S0_START][E3_K_STRING] = S3_USER_LOGIN;
	
	client_fsm_action_table[S0_START][E0_K_NULL] = client_fsm_display_welcome;
	client_fsm_action_table[S0_START][E1_K_NEW] = client_reg_fsm;

	return 0;
}

/* parse all data to generate event */
int client_fsm_data_parse( char * buf )
{
        if( strcmp(buf, EVENT_K_NEW_DATA) == 0 )
		fsm_event_insert( E1_K_NEW ); 
	else if( strcmp(buf, EVENT_K_GUEST_DATA) == 0 )
		fsm_event_insert( E2_K_GUEST ); 
	else if( strcmp(buf, EVENT_K_NULL_DATA) == 0 )
		fsm_event_insert( E0_K_NULL ); 
	else    
		fsm_event_insert( E3_K_STRING );

	return 0;
}

int client_fsm()
{
	fd_set rset, allset;
	int max_fd;
	int conn_fd = client_select_fd[1];
	char buf[64];
	int ret;
	int n;

	FD_ZERO( &allset );
	FD_SET( conn_fd, &allset );
	FD_SET( 0, &allset );
	
	max_fd = client_select_fd[1];
	//max_fd = 0;

	client_fsm_init();
	fsm_event_insert( E0_K_NULL ); 
	fsm_state_transition();

	while( 1 )
	{
		rset = allset;
		DPRINTF( "begin select ...\n" );		
		ret = select( max_fd + 1, &rset, NULL, NULL, NULL );

		if( FD_ISSET(0, &rset) )
		{
			fgets( buf, 32, stdin );
			n = strlen( buf );
			buf[n-1] = '\0';
			DPRINTF( "From Client keyboard: %s (%d bytes received) \n", buf, n-1 );

			/* all received data is parsed by client_fsm */
			client_fsm_data_parse( buf );
		}
		
		if( FD_ISSET(conn_fd, &rset) )
		{
			n = read( conn_fd, buf, sizeof(buf) );
			if( n > 0 )
			{
				buf[n] = '\0';
				DPRINTF( "From Server socket: %s (%d bytes received) \n", buf, n-1 );
			}

			/* all received data is parsed by client_fsm */
			client_fsm_data_parse( buf );
		}

		/* client fsm run once */
		fsm_state_transition();
	}

	return 0;
}
