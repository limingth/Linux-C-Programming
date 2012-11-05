/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int main( int argc, char * argv[] )
{
	char * p;
	int i; 
	printf( "hello, Cruel World! \n" );
	
	printf( "argc = %d \n", argc );
	printf( "argv[0] = %s \n", argv[0] );
	printf( "argv[1] = %s \n", argv[1] );
	printf( "argv[2] = %s \n", argv[2] );
	printf( "argv[3] = %s \n", argv[3] );

	//return 0;

	printf( "&argc = 0x%x \n", &argc );
	printf( "argv = 0x%x \n", argv );
	printf( "&argv[0] = 0x%x \n", &argv[0] );
	printf( "&argv[1] = 0x%x \n", &argv[1] );
	printf( "&argv[2] = 0x%x \n", &argv[2] );
	printf( "&argv[3] = 0x%x \n", &argv[3] );
	
//	return 0;
#if 1
	printf( "argv[0] = 0x%x \n", argv[0] );
	printf( "argv[1] = 0x%x \n", argv[1] );
	printf( "argv[2] = 0x%x \n", argv[2] );
	printf( "argv[3] = 0x%x \n", argv[3] );
#endif
//	return 0;

	p = (char *)argv[0];
	for( i = 0; i < 20; i++ )
	{
		printf( "addr[0x%x]=%c(0x%x) \n", p+i, *(p+i), *(p+i) );
	}
	
	return 0; 
}
