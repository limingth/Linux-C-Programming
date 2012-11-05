/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int foo( int para )
{
	int i ;
	int j ;
	
	printf( "<func> &para = 0x%x \n", &para );
	printf( "<func> &i = 0x%x \n", &i );
	printf( "<func> &j = 0x%x \n", &j );
	
	printf( "<func> i = 0x%x \n", i );
	printf( "<func> j = 0x%x \n", j );
	return 0;
}

int foo2( int p1, int p2, int p3, int p4, int p5 )
{
	printf( "<func2> &p1 = 0x%x \n", &p1 );
	printf( "<func2> &p2 = 0x%x \n", &p2 );
	printf( "<func2> &p3 = 0x%x \n", &p3 );
	printf( "<func2> &p4 = 0x%x \n", &p4 );
	printf( "<func2> &p5 = 0x%x \n", &p5 );

	return 0;
}


int main( int argc, char * argv[] )
{
	foo2( 5, 6, 7, 8, 9 );
	foo( 5 );
	return 0;

//	foo( 5 );
}

