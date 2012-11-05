
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_reg_fsm.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<client_reg_fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

/* different state-machine design as below */
#define EVENT_NUM		5
#define STATE_NUM		5

/* state machine transition table */
int reg_fsm_transition_table[STATE_NUM][EVENT_NUM] = { 0 };

void (*reg_fsm_action_table[STATE_NUM][EVENT_NUM])( void ) = { NULL };

/* client implement low-level functions */
int reg_state_transition( int state, int cond )
{
	return reg_fsm_transition_table[state][cond];
}

typedef void (*PF_VV)( void );
PF_VV reg_transition_action( int state, int cond )
{
	return reg_fsm_action_table[state][cond];
}

void reg_fsm_display_inputname( void );
void reg_fsm_ask_server_inputname( void );
void reg_fsm_display_inputpassword( void );
void reg_fsm_display_reinputpassword( void );

/* init fsm */
int reg_fsm_init( void )
{
	int i, j;

	/* init state machine table */
	for( i = 0; i < STATE_NUM; i++ )
		for( j = 0; j < EVENT_NUM; j++ )
		{
			reg_fsm_transition_table[i][j] = i;
			reg_fsm_action_table[i][j] = NULL;
		}
	
	/* install reg fsm hooker */
	fsm_init_install( reg_state_transition, reg_transition_action );	

	/* state 0 -> state 0, 1 */
	reg_fsm_transition_table[S0_START][E0_K_NULL] = S0_START;
	reg_fsm_transition_table[S0_START][E1_K_INPUT_USERNAME] = S1_USER_INPUT_NAME_OK;

	/* state 1 -> state 2 */
	reg_fsm_transition_table[S1_USER_INPUT_NAME_OK][E2_N_REG_NAME_OK] = S2_USER_REG_NAME_OK;

	/* state 2 -> state 3 */
	reg_fsm_transition_table[S2_USER_REG_NAME_OK][E3_K_INPUT_PASSWORD] = S3_USER_INPUT_PASSWORD_OK;
	
	/* state 3 -> state 4 */
	reg_fsm_transition_table[S3_USER_INPUT_PASSWORD_OK][E4_K_REINPUT_PASSWORD] = S4_USER_REINPUT_PASSWORD_OK;

	/* state 4 -> state 5 */
	reg_fsm_transition_table[S4_USER_REINPUT_PASSWORD_OK][E5_PASSWORD_SAME] = S5_USER_PASSWORD_OK;

	/* state 5 -> state 6 */
	reg_fsm_transition_table[S5_USER_PASSWORD_OK][E6_N_REG_OK] = S6_USER_REG_OK;

	reg_fsm_action_table[0][0] = reg_fsm_display_inputname;
	reg_fsm_action_table[0][1] = reg_fsm_ask_server_inputname;
	reg_fsm_action_table[1][2] = reg_fsm_display_inputpassword;
	reg_fsm_action_table[2][3] = reg_fsm_display_reinputpassword;
//	reg_fsm_action_table[3][4] = reg_fsm_display_password_same;
#if 0
	reg_fsm_action_table[STATE_USER_INPUT_PASSWORD_OK][] = client_view_display_welcome;
	reg_fsm_action_table[S0_START][EVENT_K_NEW] = client_view_display_inputname;
	reg_fsm_action_table[STATE_USER_REGISTER][EVENT_K_NEW] = client_view_display_notnew;
	reg_fsm_action_table[STATE_USER_REGISTER][EVENT_K_GUEST] = client_view_display_notguest;
#endif

	return 0;
}

char username[32];
char passwd1[32];
char passwd2[32];

/* parse all data to generate event */
int reg_fsm_data_parse( char * buf )
{
	if( strcmp(buf, EVENT_K_NULL_DATA) == 0 )
		fsm_event_insert( E0_K_NULL ); 
	else if( strcmp(buf, "REG_NAME_OK" ) == 0 )
		fsm_event_insert( E2_N_REG_NAME_OK );
	else
	{
		if( fsm_get_state() == 0 )
		{
			DPRINTF( "get username \n" );
			strcpy( username, buf );
			fsm_event_insert( E1_K_INPUT_USERNAME );
		}
		else if( fsm_get_state() == 2 )
		{
			DPRINTF( "get passwd1 \n" );
			strcpy( passwd1, buf );
			fsm_event_insert( E3_K_INPUT_PASSWORD );
		}
		else if( fsm_get_state() == 3 )
		{
			DPRINTF( "get passwd2 \n" );
			strcpy( passwd2, buf );
			fsm_event_insert( E4_K_REINPUT_PASSWORD );
		}
		else
			if( strcmp(passwd1, passwd2) == 0 )
				fsm_event_insert( E5_PASSWORD_SAME );
			
	}
			
#if 0
        if( strcmp(buf, EVENT_K_NEW_DATA) == 0 )
		fsm_event_insert( EVENT_K_NEW ); 
	else if( strcmp(buf, EVENT_K_GUEST_DATA) == 0 )
		fsm_event_insert( EVENT_K_GUEST ); 
	else 
#endif

	return 0;
}

extern int client_select_fd[];

int client_reg_fsm( void )
{
	fd_set rset, allset;
	int max_fd;
	int conn_fd = client_select_fd[1];
	char buf[64];
	int ret;
	int n;

	DPRINTF( "client_reg_fsm() called! \n" );

	FD_ZERO( &allset );
	FD_SET( conn_fd, &allset );
	FD_SET( 0, &allset );
	
	max_fd = client_select_fd[1];
	//max_fd = 0;

	reg_fsm_init();
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
			reg_fsm_data_parse( buf );
		}
		
		if( FD_ISSET(conn_fd, &rset) )
		{
			n = read( conn_fd, buf, sizeof(buf) );
			if( n > 0 )
			{
				buf[n] = '\0';
				DPRINTF( "From Server socket: %s (%d bytes received) \n", buf, n );
			}

			/* all received data is parsed by client_fsm */
			reg_fsm_data_parse( buf );
		}

		/* client reg fsm run once */
		fsm_state_transition();
	}
}


