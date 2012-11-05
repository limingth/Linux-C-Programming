/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>


void * p = (void *) 0;

struct t
{
	char a;
	char b;
	short c;
};

void foo( void )
{
	printf( "<foo> function called! \n" );
	printf( "<foo> foo = 0x%x \n", foo );
	return ;
}

int test = 0x33005566;

int main( int argc, char * argv[] )
{
	p = (void *) &test;

	printf( "hello, Cruel World! \n" );

	printf( "&a = 0x%x\n", p ); 

	printf( "int value = 0x%x\n", *(int *)p ); 

	printf( "char value = %c (0x%x)\n", *(char *)p, *(char *)p ); 

	printf( "float value = %f\n", *(float *)p ); 

	printf( "string value = %s\n", (char *)p ); 

	printf( "struct.a = %c (0x%x)\n", ((struct t *)p)->a,((struct t *)p)->a ); 
	printf( "struct.b = %c (0x%x)\n", ((struct t *)p)->b,((struct t *)p)->b ); 
	printf( "struct.c = %d (0x%x)\n", ((struct t *)p)->c,((struct t *)p)->c ); 

	((struct t *)p)->c = 0x1122;
	printf( "test = 0x%x \n", test );

	foo();
	(( void (*) (void) )(0x8048328))();
	return 0;

	//printf( "function entry address = 0x%x \n", foo );
	return 0;



}
