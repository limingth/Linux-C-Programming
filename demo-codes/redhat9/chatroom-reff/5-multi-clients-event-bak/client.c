#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client_fsm.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<client> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

#define LISTEN_PORT 9000
#define SERVER_IP "127.0.0.1"

int main( int argc, char *argv[] )
{
	int port = LISTEN_PORT;		/* set the port default value as LISTEN_PORT */
	char ip[16] = SERVER_IP;	/* set the ip default value as SERVER_IP */
	int conn_fd;			/* define connect fd */
	struct sockaddr_in server_addr;
	char buf[64];
	int n;
	int ret;
	fd_set rset, allset;
	int max_fd;

	/* get the server ip from command line argv[1] */
	if( argc >= 2 )
		strncpy( ip, argv[1], 16 );

	/* get the server port from command line argv[2] */
	if( argc >= 3 )
		port = atoi( argv[2] );

	DPRINTF( "client begin to connect server %s:%d \n", ip, port );
	
	/* create connect socket */
	conn_fd = socket( AF_INET,SOCK_STREAM, 0);

	/* fill in the struct */
	bzero( &server_addr, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	inet_pton( AF_INET, ip, &server_addr.sin_addr );
	server_addr.sin_port = htons( port );

	/* connect to server listen port */
	//ret = connect( conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) );
	if( ret >= 0 )
		DPRINTF( "server is connected! \n" );
	else
	{
		printf( "server is NOT connected! \n" );
		exit( 0 );
	}

	FD_ZERO( &allset );
	FD_SET( conn_fd, &allset );
	FD_SET( 0, &allset );
	
	//max_fd = conn_fd;
	max_fd = 0;

	client_fsm_init();
	client_fsm_event( EVENT_K_NULL ); 
	client_fsm_transition();	

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

			/* all received data is parsed by client_view */
			client_view_parse( buf );
		}
		
		if( FD_ISSET(conn_fd, &rset) )
		{
			n = read( conn_fd, buf, sizeof(buf) );
			if( n > 0 )
			{
				buf[n] = '\0';
				DPRINTF( "From Server socket: %s (%d bytes received) \n", buf, n-1 );
			}

			/* all received data is parsed by client_view */
			client_view_parse( buf );
		}

		/* client fsm run once */
		client_fsm_transition(); 
	}

	return 0;
}
