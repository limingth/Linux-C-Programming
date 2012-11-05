#include <finc/finapi/netapi.h>

#ifdef USING_NET_API
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/utsname.h>
#include <sys/wait.h>

#include <netinet/in_systm.h>
#include <netinet/in.h>
#include <net/if.h>
#include <netdb.h>

#include <arpa/inet.h>

int FINC_SOCK_STREAM = 0;
int FINC_SOCK_DGREAM = 1;
int FINC_SHUT_RD = SHUT_RD;
int FINC_SHUT_WR = SHUT_WR;
int FINC_SHUT_RDWR = SHUT_RDWR;

void net_init(FinC* self)
{
	finc_insert_var (self, "int", "SOCK_STREAM", &FINC_SOCK_STREAM);
	finc_insert_var (self, "int", "SOCK_DGREAM", &FINC_SOCK_DGREAM);
	finc_insert_var (self, "int", "SHUT_RD", &FINC_SHUT_RD);
	finc_insert_var (self, "int", "SHUT_WR", &FINC_SHUT_WR);
	finc_insert_var (self, "int", "SHUT_RDWR", &FINC_SHUT_RDWR);

    finc_insert_func(self, "net_socket", net_socket, "int", "int", "type", NULL);
    finc_insert_func(self, "net_bind", net_bind, "int", "int", "fd", "pointer", "addr", NULL);
	finc_insert_func(self, "net_listen", net_listen, "int", "int", "fd", "int", "backlog", NULL);
	finc_insert_func(self, "net_accept", net_accept, "int", "int", "fd", "pointer", "addr", "pointer", "addrlen", NULL);
	finc_insert_func(self, "net_send", net_send, "int", "int", "fd", "pointer", "buf", "int", "bufsize", NULL);
	finc_insert_func(self, "net_recv", net_recv, "int", "int", "fd", "pointer", "buf", "int", "bufsize", NULL);
	finc_insert_func(self, "net_close", net_close, "int", "int", "fd", NULL);
	finc_insert_func(self, "net_shutdown", net_shutdown, "int", "int", "fd", "int", "howto", NULL);
	finc_insert_func(self, "inetaddr_new", inetaddr_new, "pointer", "string", "addr", "int", "port", NULL);
	finc_insert_func(self, "inetaddr_new_any", inetaddr_new_any, "pointer", NULL);
	finc_insert_func(self, "inetaddr_destroy", inetaddr_destroy, "pointer", "ia", NULL);
	finc_insert_func(self, "inetaddr_get_name", inetaddr_get_name, "string", "pointer", "ia", NULL);
	finc_insert_func(self, "inetaddr_get_port", inetaddr_get_port, "int", "pointer", "ia", NULL);
	finc_insert_func(self, "inetaddr_set_port", inetaddr_set_port, "void", "pointer", "ia", "int", "port", NULL);
	finc_insert_func(self, "inetaddr_gethostname", inetaddr_gethostname, "string", NULL);
	finc_insert_func(self, "inetaddr_gethostaddr", inetaddr_gethostaddr, "pointer", NULL);
}

/*int socket(int type);*/
int net_socket(int type)
{
	return type==FINC_SOCK_STREAM? socket(AF_INET, SOCK_STREAM, 0) : socket(AF_INET, SOCK_DGRAM,  0);
}

/*int net_bind( int fd, pointer addr );*/
int net_bind( int fd, ADT addr )
{
	int result;
	struct sockaddr_in* p_addr;
	p_addr = (struct sockaddr_in*) addr;

	result = bind( fd, (struct sockaddr *)addr, sizeof(struct sockaddr_in) );

	return result;
}

/*int net_listen( int fd, int backlog );*/
int net_listen( int fd, int backlog )
{
	return listen(fd, backlog);
}

/*int net_accept( int fd, pointer addr, pointer addrlen );*/
int net_accept( int fd, ADT addr, ADT addrlen )
{
	return accept( fd, (struct sockaddr*) addr, (socklen_t*)addrlen );
}

/*int net_send( int fd, pointer buf, int bufsize );*/
int net_send( int fd, ADT buf, int bufsize )
{
	return send( fd, buf, bufsize , 0);
}

/*int net_recv( int fd, pointer buf, int bufsize );*/
int net_recv( int fd, ADT buf, int bufsize )
{
	int result;
	char *p;

	p = buf;
	result = recv(fd, buf, bufsize, 0);
	if ( result < bufsize-1 )
	{
		p[result] = '\0';
	}

	return result;
}

int net_close( int fd )
{
	return close(fd);
}

int net_shutdown( int fd, int howto )
{
	return shutdown( fd, howto );
}

/*pointer inetaddr_new(string addr, int port)*/
ADT inetaddr_new(char* addr, int port)
{
	struct sockaddr_in* sa_in;
	struct in_addr inaddr;

	sa_in = (struct sockaddr_in*)mem_new(sizeof(struct sockaddr_in));
	if (inet_aton(addr, &inaddr) != 0)
	{
		sa_in->sin_family = AF_INET;
		sa_in->sin_port = htons(port);
		memcpy(&sa_in->sin_addr, (char*) &inaddr, sizeof(struct in_addr));
	}
	else
	{
/*
		struct sockaddr_in sa;

		if (gethostbyname(addr, &sa, NULL))
		{
			sa_in->sin_family = AF_INET;
			sa_in->sin_port = htons(port);
			memcpy(&sa_in->sin_addr, &sa.sin_addr, 4);
		}
*/
	}

	return sa_in;
}

/*pointer inetaddr_new_any(int port);*/
ADT inetaddr_new_any()
{
	struct sockaddr_in* sa_in;

	sa_in = (struct sockaddr_in*)mem_new(sizeof(struct sockaddr_in));
	bzero(sa_in, sizeof(struct sockaddr_in));
	sa_in->sin_family = AF_INET;
	sa_in->sin_addr.s_addr = htonl(INADDR_ANY);
	sa_in->sin_port = 0;

	return sa_in;
}

/*void inetaddr_destroy(pointer self);*/
void inetaddr_destroy(ADT self)
{
	struct sockaddr_in* addr;

	addr = (struct sockaddr_in*)self;
	mem_destroy(addr);
}

/*string inetaddr_get_name(pointer ia)*/
char* inetaddr_get_name(ADT ia)
{
	char* name;
/*
	if (!ia)return NULL;

	if ((name = gethostbyaddr((char*) &((struct sockaddr_in*)&ia->sa)->sin_addr, 
		sizeof(struct in_addr), AF_INET)) != NULL)
		ia->name = name;
	else
		ia->name = inetaddr_get_canonical_name(ia);

	return g_strdup(ia->name);
*/
	return name;
}

/*int inetaddr_get_port(pointer ia)*/
int inetaddr_get_port(ADT ia)
{
	if (!ia)return 0;

	return ntohs(((struct sockaddr_in*)ia)->sin_port);
}

/*void inetaddr_set_port(pointer ia, int port)*/
void inetaddr_set_port(ADT ia, int port)
{
	if (!ia)return;

	((struct sockaddr_in*) ia)->sin_port = htons(port);
}

/*string inetaddr_gethostname()*/
char* inetaddr_gethostname(void)
{
	char* name = NULL;
	struct utsname myname;

	if (uname(&myname) < 0) return NULL;
/*
	if (!gethostbyname(myname.nodename, NULL, &name)) return NULL;
*/
	return name;
}

/*pointer inetaddr_gethostaddr()*/
ADT inetaddr_gethostaddr (void)
{
	char* name;
	ADT ia = NULL;

	name = inetaddr_gethostname();
	if (name != NULL)
	{  
		ia = inetaddr_new(name, 0);
		free(name);
	}

	return ia;
}

#endif
