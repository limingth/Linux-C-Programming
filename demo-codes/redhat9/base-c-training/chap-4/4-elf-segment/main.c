/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int var1 = 16;
int bss1;

int bss0 = 1;

int var2 = 10+2*4;
int bss2;

int * addr = 0;
int test;

char chvar[8] = "aabbcc";
//char chvar[8] = "aabbccdd";
char ch = 'A';
char ch1 = 'B';

static int ttt = -2;

int fun( void )
{
	int local = 100;
	static int s = 200;

	s = 0x1212;

	printf( "&local = 0x%x \n", &local );
	printf( "&s = 0x%x \n", &s );
}

int main( int argc, char * argv[] )
{
	int ret1 = 0;
	int ret2 = 10 + 2 * 4 + 5;

	ret1 = 2 + ret2 * 9 ;
	ret2 = var1 - var2;

	bss2 = var1 + bss1;

	printf( "hello, Cruel World! \n" );

	printf( "&bss0 = 0x%x \n", &bss0 );
	printf( "&bss1 = 0x%x \n", &bss1 );
	printf( "&bss2 = 0x%x \n", &bss2 );

	printf( "&ret1 = 0x%x \n", &ret1 );
	printf( "&ret2 = 0x%x \n", &ret2 );

	printf( "&var1 = 0x%x \n", &var1 );
	printf( "&var2 = 0x%x \n", &var2 );

	printf( "str = %s \n", chvar );

	fun();
	return 0; 
}

