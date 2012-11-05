/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

char str[] = "hello, world!";
char * pstr = "HELLO, WORLD!";

char * pstr2 = 0;

int main( int argc, char * argv[] )
{
	int i;

	printf( "hello, Cruel World! \n" );

	printf( "str = %s \n", str );
	printf( "pstr = %s \n", pstr );

//	return 0;

	pstr = str;

	pstr[1] = '1';
	*(pstr++)= '2';
	*(pstr+1) = '3';
	printf( "2 pstr = %s \n", pstr );
	
	str[1] = '-';
	//*(str++) = '-';

	printf( "2 str = %s \n", str );
	printf( "2 pstr = %s \n", pstr );
	return 0;

	//str[1] = '9';
	pstr = str;
	*(pstr+1) = '9';

	for( i = 0; i<24; i++ )
		printf( "pstr+%d = '%c'(=0x%x) \n", i, *(pstr+i), *(pstr+i) );

	printf( "str = %s \n", str );
	printf( "pstr = %s \n", pstr );

	return 0;
}
