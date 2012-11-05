/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

//int a = 0x00310035;
int a = 0x8048328;

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

int main( int argc, char * argv[] )
{
	void (*p2) (void) = a;

	p2();
	return 0;
	p = (void *) &a;

	printf( "hello, Cruel World! \n" );
	printf( "hello, Cruel World! \n", *p );

	printf( "int value = 0x%x \n", *(int *)p ); 
	printf( "char value = %c \n", *(char *)p ); 
	printf( "short value = 0x%x \n", *(short *)p ); 
	printf( "string value = %s \n", (char *)p ); 

	printf( "struct.a = %c \n", ((struct t *)p)->a ); 
	printf( "struct.b = %c \n", ((struct t *)p)->b ); 
	printf( "struct.c = %d \n", ((struct t *)p)->c ); 
	((struct t *)p)->b = 0x30;
	printf( "a = 0x%x \n", a );
	
	printf( "float value = %f \n", *(float *)p ); 
//	return 0;

	printf( "string value = %s \n", (char *)p ); 
	printf( "pointer address = 0x%x \n", p );
	
	foo();
}
