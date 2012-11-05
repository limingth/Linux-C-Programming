/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>
void test( void );
char str[100] = "hello /*ccc*/ world "; /* ccc */ char str2[100]="abcd";

/* ccc */
int main( int argc, char * argv[] )
{
	printf( "hello, Cruel World! \n" );
	
	printf( "it is NOT /* ccc */ comment \n" );

	printf( "aaa" ); /* ccc */  printf( "bbb" );

	test();

	return 0; 
}

void test( void )
{
	char a = '"';   /* ccc */    char b = '"';

	char c = '"'; \
	char d = '"'; \

	printf( "\"\n");
	printf( "\"\"\n");
	printf( "\"/* ccc */\"\n" );
	printf( "\"/* \"ccc\" */\"\n" );
	printf( "'\"'/* ccc */'\"'\n" );
	printf( "'\"'/* \"ccc\" */'\"'\n" );

	return;
}
