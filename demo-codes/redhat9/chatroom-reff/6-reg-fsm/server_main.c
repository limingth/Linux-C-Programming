#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#include "public.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<server_main> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif


#define LISTEN_PORT 9000
int listen_fd;			/* define server listen fd */

void sig_pipe( int signo )
{
	printf( "sig_pipe envoked! \n" );
	return;
}

void sig_int( int signo )
{
	printf( "sig_int envoked! \n" ); 
	close( listen_fd );
	exit( 0 );
	return;
}

int main( int argc, char *argv[] )
{
	int port = LISTEN_PORT;		/* set the port default value as PORT */
	struct sockaddr_in server_addr;
	int total = 0, i, j;
	int ret;

	struct sigaction newact, oldact;

	/* set our handler, save the old one */
	newact.sa_handler = sig_int;
	newact.sa_flags = 0;
	sigaction(SIGINT, &newact, &oldact );

	/* set our handler, save the old one */
	newact.sa_handler = sig_pipe;
	newact.sa_flags = 0;
	sigaction(SIGPIPE, &newact, &oldact );

	/* get the listen port from command line argv[1] */
	if( argv[1] )
		port = atoi( argv[1] );

	printf( "server begin at port: %d \n", port );
	
	/* create socket and listen */
	listen_fd = socket( AF_INET,SOCK_STREAM, 0);

	/* fill in the struct */
	bzero( &server_addr, sizeof(server_addr) );
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	server_addr.sin_port = htons( port );

	/* bind server listen port */
	ret = bind( listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr) );
	if( ret < 0 )
		printf( "server bind error !\n" );

	/* server begin to listen */
	listen( listen_fd, 8 );
	printf( "Accepting connections: %d \n", port );
	
	server_fsm();

	return 0;
}

