/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

struct hole
{
#if 0
	char a;
	int b;
	short c;
	char d;
#endif
	//int i;
	char a[10];
};
	
struct no_hole
{
	int b;
	short c;
	char a;
	char d;
};

struct hole a = { 'a', 0x11223344, 0x8899, 'd' };
struct no_hole b = { 0xb, 0xc, 'a', 'd' };

int main( int argc, char * argv[] )
{
	printf( "hello, Cruel World! \n" );

	printf( "sizeof hole = %d \n", sizeof(a) );
	printf( "sizeof no_hole = %d \n", sizeof(b) );

	return 0;
}


