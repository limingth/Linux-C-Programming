/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

struct 
{
	int len;
	char * str;
} a, *p;

int main( int argc, char * argv[] )
{
	int i;
	char * pp;
	printf( "hello, Cruel World! \n" );
	a.len = 10;
	a.str = "abcd";
	printf( "1 a.len = %d \n", a.len );
	printf( "2 a.str = %s \n", a.str );
	//strcpy( a.str, "aabb" );
	printf( "3 a.str = %s \n", a.str );

	p = malloc( 32 );
	p->len = 10;
	printf( "4 p->len = %d \n", p->len );

	p->str = "12345678";
	printf( "5 p->str = %s \n", p->str );
	
	p->str = malloc( 2 );
	printf( "a p->str = 0x%x \n", p->str );
	pp = p->str;
	for ( i = 0; i<10; i++ )
		printf( "*p = %d\n", *pp ); 

	p->str = malloc( 20 );
	pp = p->str;
	for ( i = 0; i<100; i++ )
		printf( "2 *p = %d\n", *pp ); 
	printf( "b p->str = 0x%x \n", p->str );
	strcpy( p->str, "aabb" );
	printf( "6 p->str = %s \n", p->str );
	return 0;
}


