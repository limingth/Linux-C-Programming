#ifndef _NET_API_H
#define _NET_API_H

#include <finc/fincconfig.h>
#ifdef USING_NET_API
#include <tiny/object.h>

#include <finc/finclib.h>
#include <finc/fincdata.h>
#include <finc/finctype.h>

void net_init(FinC* self);
int net_socket(int type);
int net_bind( int fd, ADT addr );
int net_listen( int fd, int backlog );
int net_accept( int fd, ADT addr, ADT addrlen );
int net_send( int fd, ADT buf, int bufsize );
int net_recv( int fd, ADT buf, int bufsize );
int net_close( int fd );
int net_shutdown( int fd, int howto );
ADT inetaddr_new(char* addr, int port);
ADT inetaddr_new_any();
void inetaddr_destroy(ADT self);
char* inetaddr_get_name(ADT ia);
int inetaddr_get_port(ADT ia);
void inetaddr_set_port(ADT ia, int port);
char* inetaddr_gethostname(void);
ADT inetaddr_gethostaddr (void);

#endif

#endif
