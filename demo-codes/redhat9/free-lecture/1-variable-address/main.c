/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int global_a = 10;
int global_b = 20;

static int static_a = 1000;

int main( int argc, char * argv[] )
{
	int local_a = 100;
	int local_b = 200;

	static int static_b = 0;
	
	int * p = (int *)&static_a;

	printf( "<main.c> address local_a = 0x%x \n", &local_a );
	printf( "<main.c> address local_b = 0x%x \n", &local_b );

	printf( "<main.c> address global_a = 0x%x \n", &global_a );
	printf( "<main.c> address global_b = 0x%x \n", &global_b );

//	return 0;

	printf( "<main.c> 1 static_b = %d \n", static_b );
	*(p+1) = 2000;
	printf( "<main.c> 2 static_b = %d \n", static_b );

//	return 0;

	*(p-1) = 2;
	*(p-2) = 1;
	printf( "<main.c> global_a = %d \n", global_a );
	printf( "<main.c> global_b = %d \n", global_b );

	return 0;
}
