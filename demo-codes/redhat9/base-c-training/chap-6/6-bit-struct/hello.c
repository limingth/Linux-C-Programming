/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

struct flag
{
	unsigned int is_keyword : 1;
	unsigned int is_extern : 4;
	unsigned int is_static : 1;
	unsigned int is_mid : 20;
	unsigned int is_high : 1;
	unsigned int is_highest : 1;
} flags;
int main( int argc, char * argv[] )
{
	flags.is_keyword = 1;
	flags.is_extern = 4;
	flags.is_mid = 3;
	flags.is_high = 1;
	printf( "flags = 0x%x \n", flags );
	printf( "sizeof flags = %d \n",sizeof(flags) );

	return 0;
}


