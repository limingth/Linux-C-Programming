/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

union u_tag 
{
	unsigned char c[4];
	int i;
//	double d;
	struct 
	{
		char a;
		char b;
		short d;	
		int age;
	} d;
} u;

#define printc( expr )	printf( #expr " = %c \n", expr )
//#define printi( expr )	printf( #expr " = %d \n", expr )
#define printi( expr )	printf( "<int> " #expr " = %d \n", expr )
#define printd( expr )	printf( #expr " = %f \n", expr )

#define printx( expr )	printf( #expr " = 0x%x \n", expr )

int main( int argc, char * argv[] )
{
	printf( "hello, Cruel World! \n" );

	printf( "sizeof u_tag = %d \n", sizeof(u) );
	printf( "sizeof double = %d \n", sizeof(double) );


	u.i = 0x12345678;
	printf( "u.d.a = 0x%x \n", u.d.a);
	printf( "u.d.b = 0x%x \n", u.d.b);
	printf( "u.d.d = 0x%x \n", u.d.d);
	return 0;

	printx( u.c[0] );
	printx( u.c[1] );
	printx( u.c[2] );
	printx( u.c[3] );
	printx( u.c[4] );
	printx( u.c[5] );
	printx( u.c[6] );
	printx( u.c[7] );

	return 0;
	u.c[3] = 48;

	printx( u.i );

	printd( u.d );
	return 0;
}

