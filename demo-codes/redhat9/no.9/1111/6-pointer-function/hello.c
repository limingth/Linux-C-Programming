/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int add( int a, int b )
{
	printf( "add called!\n" );
	return a+b;
}

int sub( int a, int b )
{
	printf( "sub called!\n" );
	return a-b;
}

#if 0
int * f (int a, int b);
#endif

int (*f)(int, int) = 0;
int (*f0)(int) = 0;

int (*fa[2])( int, int );

int main( int argc, char * argv[] )
{
	int ret = 0;
	printf( "hello, Cruel World! \n" );

	ret = add( 1, 2 );
	printf( "ret = add(1, 2) = %d \n", ret );

	ret = sub( 1, 2 );
	printf( "ret = sub(1, 2) = %d \n", ret );

//	return 0;

	f = add;
	f0 = add;
	printf( "f = add = 0x%x \n", f );
	printf( "->> add = %d \n", (*f)(100,200) );
	printf( "->> 2 add = %d \n", (*f0)(100) );
	return 0;

	f = sub;
	printf( "f = sub = 0x%x \n", f );
	printf( "sub = %d \n", f(100,200) );

	//return 0;

	fa[0] = add;
	printf( "fa[0](100,200) add = %d \n", fa[0](100,200) );
	fa[1] = sub;
	printf( "fa[1](100,200) sub = %d \n", fa[1](100,200) );

	printf( "fa[0] addr = 0x%x \n", fa[0] );
	printf( "fa[1] addr = 0x%x \n", fa[1] );

	return 0;
}
