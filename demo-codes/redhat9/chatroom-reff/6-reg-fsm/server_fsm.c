#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "server_fsm.h"
#include "public.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<server_fsm> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

int listen_fd;			/* define server listen fd */
int user_fd[32] = { 0 };	/* max user number 32 */
int online_user = 0;		/* all online user number */

/* different state-machine design as below */
#define EVENT_NUM		5
#define STATE_NUM		5

/* state machine transition table */
int server_fsm_transition_table[STATE_NUM][EVENT_NUM] = { 0 };

void (*server_fsm_action_table[STATE_NUM][EVENT_NUM])( void ) = { NULL };

/* server implement low-level functions */
int server_state_transition( int state, int cond )
{
	return server_fsm_transition_table[state][cond];
}

typedef void (*PF_VV)( void );
PF_VV server_transition_action( int state, int cond )
{
	return server_fsm_action_table[state][cond];
}

/* init fsm */
int server_fsm_init( void )
{
	int i, j;

	/* init state machine table */
	for( i = 0; i < STATE_NUM; i++ )
		for( j = 0; j < EVENT_NUM; j++ )
		{
			server_fsm_transition_table[i][j] = i;
			server_fsm_action_table[i][j] = NULL;
		}
	
	/* install fsm hooker */
	fsm_init_install( server_state_transition, server_transition_action );	

	/* state 0 -> state 0, 1, 2, 3 */
	server_fsm_transition_table[S0_START][E0_L_NULL] = S0_START;
	server_fsm_transition_table[S0_START][E1_L_REG_NAME_OK] = S1_USER_REGISTER;
	server_fsm_transition_table[S0_START][E2_L_LOGIN_OK] = S2_USER_ONLINE;

	server_fsm_transition_table[S0_START][E3_L_REG_NAME_RESERVED] = S0_START;
	server_fsm_transition_table[S0_START][E4_L_REG_NAME_EXIST] = S0_START;
	server_fsm_transition_table[S0_START][E5_L_LOGIN_NAME_ERR] = S0_START;
	server_fsm_transition_table[S0_START][E6_L_LOGIN_PASSWORD_ERR] = S0_START;
	
	/* state 1 -> state 2 */
	server_fsm_transition_table[S1_USER_REGISTER][E7_L_UPDATE_OK] = S2_USER_ONLINE;

	/* state 2 -> state 3 */
	server_fsm_transition_table[S2_USER_ONLINE][E8_L_LOGOUT] = S3_USER_OFFLINE;

#if 0
	server_fsm_action_table[S0_START][E0_K_NULL] = server_fsm_display_welcome;
	server_fsm_action_table[S0_START][E1_K_NEW] = server_reg_fsm;
#endif

	return 0;
}

int net_event_generate( int conn_fd )
{
	int len;
	int n;
	char type;
	char buf[256];
	char str[128];

	n = read( conn_fd, buf, 2 );
	DPRINTF( "From Server socket: 0x%x %d (%d bytes received) \n", buf[0], buf[1], n );

	if( n != 2 )
	{
		printf( "Server socket read error! \n" );
		exit(0);
	}
	
	switch( buf[0] )
	{
		case P1_C_REG_NAME:
			strcpy( str, "Server: Yourname: " );		
			buf[0] = P2_S_HINT_REGISTER;
			len = strlen(str);
			buf[1] = len;
			strcpy( &buf[2], str );
			write( conn_fd, buf, len+2 );
			printf( "server send P2_S_HINT_REGISTER packet to client \n" );


			break;
	}	
}


/* parse all data to generate event */
int server_fsm_data_parse( char * buf )
{
#if 0
        if( strcmp(buf, EVENT_K_NEW_DATA) == 0 )
		fsm_event_insert( E1_K_NEW ); 
	else if( strcmp(buf, EVENT_K_GUEST_DATA) == 0 )
		fsm_event_insert( E2_K_GUEST ); 
	else if( strcmp(buf, EVENT_K_NULL_DATA) == 0 )
		fsm_event_insert( E0_K_NULL ); 
	else    
		fsm_event_insert( E3_K_STRING );
#endif

	return 0;
}

void server_fsm( void )
{
	int max_fd;			/* for select() use */
	int conn_fd;			/* define connect fd */
	fd_set allset, rset;
	int ret;
	socklen_t user_addr_len;
	struct sockaddr_in user_addr;
	char str[32];
	char buf[256];
	char * cip;
	char cport[32];
	int total = 0, i, j;
	char len;

	max_fd = listen_fd;
	FD_ZERO( &allset );
	FD_SET( listen_fd, &allset );

	while( 1 )
	{
		rset = allset;

		printf( "begin to select ... \n" );
		ret = select( max_fd + 1, &rset, NULL, NULL, NULL );
		if( ret < 0 )
			printf( "select error! \n" );

		if( FD_ISSET(listen_fd, &rset) )
		{
			user_addr_len = sizeof( user_addr );
			conn_fd = accept( listen_fd, (struct sockaddr *)&user_addr, &user_addr_len );
			
			printf( "user %d is connected from %s:%d \n", 
				online_user,
				inet_ntop(AF_INET, &user_addr.sin_addr, str, sizeof(str)),
				ntohs(user_addr.sin_port) );
			
			char str[128] = "Connected OK. welcome to AKAE chatroom! \nPlease input: (new, guest, yourname) ";
			buf[0] = P1_S_WELCOME;
			len = strlen(str);
			buf[1] = len;
			strcpy( &buf[2], str );
			write( conn_fd, buf, len+2 );
			printf( "server send P1_S_WELCOME packet to client \n" );

			cip = (char *)inet_ntop(AF_INET, &user_addr.sin_addr, str, sizeof(str));
			//cport = itoa( ntohs(user_addr.sin_port) );
			sprintf( cport, "%d", ntohs(user_addr.sin_port) ); 
			//sprintf( cport, "%d", conn_fd ); 
			
			/* save the conn_fd to user_fd[] */
			user_fd[online_user] = conn_fd;

			/* add a new online_user */
			online_user++;
			FD_SET( conn_fd, &allset );
			//user_online_add( cport, cip, conn_fd );
			
			/* change the max_fd */
			if( conn_fd > max_fd )
				max_fd = conn_fd;
			
			continue;
		}	

		printf( "checking every online users. \n" );
		for( i = 0; i < online_user; i++ )
		{
			conn_fd = user_fd[i];
			printf( "check fd: %d (max:%d) \n", conn_fd, max_fd );

			if( FD_ISSET(conn_fd, &rset) )
			{
				net_event_generate( conn_fd );
			}

#if 0
					sprintf( str, "%d", conn_fd ); 
					if( strcmp( buf, "quit" ) )
						user_online_del( str );

					for( j = 0; j < online_user; j++ )
					{
						printf( "Write To Client %d: %s \n", user_fd[j], buf );
						//write( user_fd[j], buf, strlen(buf) );
						write( user_fd[j], "REG_NAME_OK", 11 );
					}
#endif
		}
	}
	return;
}
