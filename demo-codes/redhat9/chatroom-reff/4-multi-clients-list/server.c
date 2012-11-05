#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>


#define LISTEN_PORT 9000
void sig_pipe( int signo )
{
	printf( "sig_pipe envoked! \n" );
	return;
}

void sig_int( int signo )
{
	printf( "sig_int envoked! \n" ); 
	
	return;
}

int main( int argc, char *argv[] )
{
	int port = LISTEN_PORT;		/* set the port default value as PORT */
	int listen_fd;			/* define server listen fd */
	int conn_fd;			/* define connect fd */
	int max_fd;			/* for select() use */
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len;
	char str[32];
	char buf[32];
	int total = 0, i, j;
	int ret;
	fd_set allset, rset;
	int client_fd[32] = { 0 };	/* max client number 32 */
	int online_client = 0;		/* all online client number */
	char * cip;
	char cport[32];

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
			client_addr_len = sizeof( client_addr );
			conn_fd = accept( listen_fd, (struct sockaddr *)&client_addr, &client_addr_len );
			
			printf( "client is connected from %s:%d! \n", 
				inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)),
				ntohs(client_addr.sin_port) );
			
			cip = (char *)inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str));
			//cport = itoa( ntohs(client_addr.sin_port) );
			//sprintf( cport, "%d", ntohs(client_addr.sin_port) ); 
			sprintf( cport, "%d", conn_fd ); 
			
			/* save the conn_fd to client_fd[] */
			client_fd[online_client] = conn_fd;

			/* add a new online_client */
			online_client++;
			FD_SET( conn_fd, &allset );
			user_online_add( cport, cip, conn_fd );
			
			/* change the max_fd */
			if( conn_fd > max_fd )
				max_fd = conn_fd;
			
			//continue;
		}	

		printf( "checking every online clients. \n" );
		for( i = 0; i < online_client; i++ )
		{
			conn_fd = client_fd[i];
			printf( "check fd: %d (max:%d) \n", conn_fd, max_fd );

			if( FD_ISSET(conn_fd, &rset) )
			{
				//	while( 1 )
				{
					if( (ret = read(conn_fd, buf, 32)) > 0 )
					{	
						buf[ret] = '\0';
						printf( "From Client: %s", buf );

						sprintf( str, "%d", conn_fd ); 
						if( strcmp( buf, "quit" ) )
							user_online_del( str );

						for( j = 0; j < online_client; j++ )
						{
							printf( "Write To Client %d: %s \n", client_fd[j], buf );
							write( client_fd[j], buf, strlen(buf) );
						}
					}
					else if( ret == 0 )
					{
						printf( "client socket is closed! \n" );
						close( conn_fd );
						exit( 0 );
					}
				}
			}
		}
		printf( "end of select ... \n" );
	}
	return 0;
}
