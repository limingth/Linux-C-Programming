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

#include "public.h"

int client_select_fd[2];

int client_fsm();

int main( int argc, char *argv[] )
{
	int port = LISTEN_PORT;		/* set the port default value as LISTEN_PORT */
	char ip[16] = SERVER_IP;	/* set the ip default value as SERVER_IP */
	int conn_fd;			/* define connect fd */
	struct sockaddr_in server_addr;
	int ret;

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
	ret = connect( conn_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) );
	if( ret >= 0 )
		DPRINTF( "server is connected! \n" );
	else
	{
		printf( "server is NOT connected! \n" );
		exit( 0 );
	}

	client_select_fd[0] = 0;
	client_select_fd[1] = conn_fd;

	/* call client fsm to run */
	client_fsm();
		
	return 0;
}


