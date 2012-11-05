
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "client_fsm.h"
#include "public.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<client_fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

/* different state-machine design as below */ 
#define COND_NUM		8
#define STATE_NUM		8

/* state machine transition table */
int client_fsm_transition_table[STATE_NUM][COND_NUM] = { 0 };

int client_fsm_condition_table[STATE_NUM][COND_NUM] = { 0 };

void (*client_fsm_action_table[STATE_NUM][COND_NUM])( void ) = { NULL };

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

void client_reg_name( void )
{
	int conn_fd = client_select_fd[1];
	char buf[256];
	char str[128] = "Server: please input your name:";
	int len;

	buf[0] = P1_C_REG_NAME;          
	len = strlen( str );
	buf[1] = len;
	write( conn_fd, buf, len+2 );
	printf( "server send P1_C_REG_NAME packet to server \n" );
}

/* init fsm */
int client_fsm_init( void )
{
	int i, j;

	/* init state machine table */
	for( i = 0; i < STATE_NUM; i++ )
		for( j = 0; j < COND_NUM; j++ )
		{
			client_fsm_transition_table[i][j] = i;
			client_fsm_action_table[i][j] = NULL;
		}
	
	/* install fsm hooker */
	fsm_init_install( client_state_transition, client_transition_action );	

	/* state 0 -> state 0, 1, 2, 3 */
	client_fsm_transition_table[S0_START][C0_K0_INPUT_NULL] = S0_START;
	client_fsm_transition_table[S0_START][C1_N1_WELCOME] = S1_WAIT_USER_CHOICE;

	client_fsm_transition_table[S1_WAIT_USER_CHOICE][C2_K1_INPUT_NEW] = S2_NEW_USER_REGISTER;

	client_fsm_transition_table[S2_NEW_USER_REGISTER][C3_N2_HINT_REGISTER] = S3_WAIT_USER_NAME;

	client_fsm_transition_table[S3_WAIT_USER_NAME][C4_K2_INPUT_NAME] = S4_WAIT_SERVER_CHECK_USER_NAME;

	client_fsm_transition_table[S4_WAIT_SERVER_CHECK_USER_NAME][C5_N3_REG_NAME_OK] = S5_WAIT_USER_INFO;

	client_fsm_transition_table[S5_WAIT_USER_INFO][C6_K3_INPUT_INFO] = S6_WAIT_SERVER_UPDATE_USER_INFO;
	
	client_fsm_transition_table[S6_WAIT_SERVER_UPDATE_USER_INFO][C7_N4_UPDATE_INFO_OK] = S7_CHAT;
	
	//client_fsm_action_table[S0_START][E0_K_NULL] = client_fsm_display_welcome;

	client_fsm_action_table[S1_WAIT_USER_CHOICE][C2_K1_INPUT_NEW] = client_reg_name;

	return 0;
}

int net_event_generate( int conn_fd )
{
	int len;
	int n;
	char type;
	char buf[256];

	n = read( conn_fd, buf, 2 );
	DPRINTF( "From Server socket: 0x%x %d (%d bytes received) \n", buf[0], buf[1], n );

	if( n != 2 )
	{
		printf( "Server socket read error! \n" );
		exit(0);
	}
	
	switch( buf[0] )
	{
		case P1_S_WELCOME:
			fsm_event_insert( C1_N1_WELCOME ); 
			len = buf[1];
			n = read( conn_fd, buf, len );
			printf( "read %d bytes \n", n );
			printf( "%s \n", buf );
			break;
		case P2_S_HINT_REGISTER:
			fsm_event_insert( C3_N2_HINT_REGISTER ); 
			len = buf[1];
			n = read( conn_fd, buf, len );
			printf( "read %d bytes \n", n );
			printf( "%s \n", buf );
	}	
}

int keyboard_event_generate( int fd )
{
	char buf[64];
	int n;

	fgets( buf, 32, stdin );
	n = strlen( buf );
	buf[n-1] = '\0';
	DPRINTF( "From Client keyboard: %s (%d bytes received) \n", buf, n-1 );

	if( strcmp(buf, "") == 0 )
		fsm_event_insert( C0_K0_INPUT_NULL ); 
	else if( strcmp(buf, "new") == 0 )
		fsm_event_insert( C2_K1_INPUT_NEW ); 
	else    
	{	// should be K_INPUT_STRING
		switch( fsm_get_state() )
		{
			case S3_WAIT_USER_NAME:
				fsm_event_insert( C4_K2_INPUT_NAME ); 
				break;
			case S5_WAIT_USER_INFO:
				fsm_event_insert( C6_K3_INPUT_INFO ); 
				break;
			default:
				fsm_event_insert( C0_K0_INPUT_NULL ); 
				break;
		}		
	}

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
	//fsm_event_insert( E0_K_NULL ); 
	//fsm_state_transition();

	while( 1 )
	{
		rset = allset;
		DPRINTF( "begin select ...\n" );		
		ret = select( max_fd + 1, &rset, NULL, NULL, NULL );

		if( FD_ISSET(0, &rset) )
		{
			keyboard_event_generate( 0 );

		}
		
		if( FD_ISSET(conn_fd, &rset) )
		{
			net_event_generate( conn_fd );
		}

		/* client fsm run once */
		fsm_state_transition();
	}

	return 0;
}
