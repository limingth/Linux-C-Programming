/*
 * user_online.c - manage online user list
 * author: li ming <limingth@akaedu.org>
 * date: 2008/9/1
 * 
 */

#include <stdlib.h>
#include "list.h"

#define DPRINTF( fmt, args... )		printf( fmt, ##args )
//#define DPRINTF( fmt, args... )	

struct user_online
{
	struct list_head list;

	/* user info from here down */
	char name[32];		/* unique id of user */
	char nickname[32];	/* user nickname, can be same for 2 user */
	int conn_fd;		/* socket fd for communicate */
	int mode;		/* user power: admin/user/guest */
	int state;		/* current state: online/offline/mute/hide */
	//struct user_msg * head;
};

typedef struct user_online user_online_t;

static LIST_HEAD( user_online_list );

static user_online_t * _user_online_new( char * name, char * nickname, int conn_fd )
{
	user_online_t * client;

	client = (user_online_t *)malloc( sizeof(user_online_t) );
	strcpy( client->name, name );
	strcpy( client->nickname, nickname );
	client->conn_fd = conn_fd;

	return client;
}

/* this function must be known that user NOT exists in list */
static user_online_t * _user_online_add( user_online_t * user )
{
        list_add_tail( &user->list, &user_online_list );
	return user;
}

/* this function must be known that user exists in list */
static user_online_t * _user_online_del( user_online_t * user )
{
        list_del( &user->list );
	free( user );
	return NULL;
}

/* print all online user info */
void user_online_print( void )
{
	user_online_t * user;

	printf( "---- online user list ---- \n" );
        list_for_each_entry( user, &user_online_list, list )
        {
		printf( "user name: %s (%s) \t fd: %d \n", user->name, user->nickname, user->conn_fd );
        }
	printf( "-------------------------- \n" );
	return;
}

/* try to find if user name already exists */
user_online_t * user_online_find( char * name )
{
	user_online_t * user;

        list_for_each_entry( user, &user_online_list, list )
        {
		DPRINTF( "user name: %s \t nickname: %s \t fd: %d \n", user->name, user->nickname, user->conn_fd );
		if( strcmp(name, user->name) == 0 )
		{
			DPRINTF( "find user %s \n", user->name );
			return user;
		}
        }

	return NULL;
}

/* try to add a new user in list */
int user_online_add( char * name, char * nickname, int conn_fd )
{
	user_online_t * user;

	/* try to find if this name exist in online user list */
	user = user_online_find( name );
	if( user != NULL )
	{
		DPRINTF( "user %s already exists in online user list! \n", name );
		return 0;
	}

	/* if not exists, then add this user */
	user = _user_online_new( name, nickname, conn_fd ); 
	_user_online_add( user ); 

	user_online_print();
	return 1;
}

/* try to del a user in list */
int user_online_del( char * name )
{
	user_online_t * user;

	/* try to find if this name exist in online user list */
	user = user_online_find( name );
	if( user == NULL )
	{
		DPRINTF( "user %s not exists in online user list! \n", name );
		return 0;
	}

	/* if exists, then del this user */
	_user_online_del( user ); 

	user_online_print();
	return 1;
}

#if 0
int main( void )
{
	user_online_t * user;
	struct list_head * node;
	int counter = 0;
	int ret = 0;

	printf( "test list! \n" );

        ret = user_online_add( "aa", "AA", 3 ); 
        ret = user_online_add( "bb", "BB", 4 );
        ret = user_online_add( "cc", "CC", 5 );
        ret = user_online_add( "dd", "DD", 6 );
        ret = user_online_add( "aa", "AAA", 30 ); 

	user = user_online_find( "dd" );
	if( user )
		printf( "user: %s exists! \n", user->name );
	
	user_online_del( "dd" );
	user = user_online_find( "dd" );
	if( user )
		printf( "user: %s exists! \n", user->name );
	else
		printf( "user: not exists! \n" );

	user_online_print();

	return 0;
}	
#endif 
