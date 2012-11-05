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
	char c;
	int i;
	char d;
};
	
typedef struct hole HOLE;

HOLE a = { 'H', 1, 'o' };

HOLE * b;

#define printc( expr )	printf( #expr " = %c \n", expr )
#define printd( expr )	printf( #expr " = %d \n", expr )



typedef int (*PFI)(int, int);

PFI f, f2, f3;

int add( int a, int b )
{
	return a+b;
}

typedef struct student
{
	char name[10];
	int age;
} STU, *PSTU;


int main( int argc, char * argv[] )
{
	STU  zs;
	PSTU  p_zs = &zs;

	printf( "hello, Cruel World! \n" );

	printf( "sizeof hole = %d \n", sizeof(a) );

	b = &a;
	
	printf( "b->c = %c \n", b->c );
	printd( b->i );
	printc( b->d );
	
	f = add;
	int ret = f( 1, 2 );	
	printd( ret );
	return 0;
}

