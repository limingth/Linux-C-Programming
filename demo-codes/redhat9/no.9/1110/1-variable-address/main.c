/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int a_out = 10;
int b_out = 20;
int c_out = 20;

static int sta_a_out = 200;

int main( int argc, char * argv[] )
{
	int a = 100;
	int b = 200;
	int c = 300;

	static int sta_a_in = 100;

	printf( "<main.c> address sta_a_in = 0x%x \n", &sta_a_in );
	printf( "<main.c> address sta_a_out = 0x%x \n", &sta_a_out );

	printf( "<main.c> address a = 0x%x \n", &a );
	printf( "<main.c> address b = 0x%x \n", &b );
	printf( "<main.c> address c = 0x%x \n", &c );

	printf( "<main.c> aaddress a_out = 0x%x \n", &a_out );
	printf( "<main.c> aaddress b_out = 0x%x \n", &b_out );
	printf( "<main.c> aaddress c_out = 0x%x \n", &c_out );

//	return 0;

	add( a, b );
	return 0;

	// int * p;
	//*p = 123;
	add( a, b );
	//printf( "sta_a = %d \n", *p);

	return 0;
}
