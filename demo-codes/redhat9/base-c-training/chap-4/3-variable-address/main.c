/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#define MAX	5
#define MIN	0

int globle_var = 0x1234;
const int const_num = 0x9999;

int add( int, int );
int sub( int, int );

int a_out = 10;
int b_out = 20;
int c_out = 300;

int main( int argc, char * argv[] )
{
	int a = 100;
	int b = 200;
	int c = 300;
	int * p = 0x804972c;

	printf( "<main.c> address a = 0x%x \n", &a );
	printf( "<main.c> address b = 0x%x \n", &b );
	printf( "<main.c> address c = 0x%x \n", &c );
	printf( "<main.c> address argc = 0x%x \n", &argc );

	sleep(1);
	for( p = 0xc0000000 - 4; p>&a; p-- )
		printf( "p(0x%x) = 0x%x \n", p, *p );
		
	printf( "<main.c> aaddress a_out = 0x%x \n", &a_out );
	printf( "<main.c> aaddress b_out = 0x%x \n", &b_out );
	printf( "<main.c> aaddress c_out = 0x%x \n", &c_out );

	return 0;

	add( a, b );
	//return 0;

	*p = 123;
	add( a, b );
	//printf( "sta_a = %d \n", *p);

	return 0;
}
