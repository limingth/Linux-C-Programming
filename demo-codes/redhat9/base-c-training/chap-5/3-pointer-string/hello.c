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

	//pstr = "abcd";
	//str = "abcd";

	printf( "str = %s \n", str );
	printf( "str = 0x%x \n", str );
	printf( "pstr = %s \n", pstr );

	//pstr = str;
	pstr[1] = '1';
	printf( "9 pstr = %s \n", pstr );
	*(pstr++)= '2';
	*(pstr+1) = '3';
	printf( "2 pstr = %s \n", pstr );
	return 0;
	
	str[1] = 'a';
	//*(str++) = 'b';
	*(str+1) = 'c';

	*(char *)(0x804951c+2) = 'd';

	printf( "2 str = %s \n", str );
	return 0;

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
