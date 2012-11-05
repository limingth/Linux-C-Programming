/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>


char name2[][15] = { "123", "456", "789", "000" };

int main( int argc, char * argv[] )
{
	char temp;
	char * name[] = { "Illegal month", "Jan", "Feb", "Mar" };
	printf( "hello, Cruel World! \n" );

	//name++;
	//name2++;

	printf( "name2 = 0x%x \n", name2 );
	printf( "name2[1] = 0x%x \n", name2[1] );


	printf( "name = 0x%x \n", name );
	//printf( "name = %s \n", name );
	printf( "-->> name[0] = 0x%x \n", name[0] );
	printf( "name[1] = %s \n", name[1] );
	printf( "name[2] = %s \n", name[2] );
	printf( "name[3] = %s \n", name[3] );

//	return 0;

	//name2[0] = name[0];

	printf( "1 name2[0] = %s \n", name2[0] );

	//name2[0][0] = name[0];

	temp = name2[0][0];
	printf( "name2[0][0] = 0x%x %d \n", temp, temp );

	printf( "%x \n", 'I' );
	printf( "name[0] = %s \n", name[0] );
	printf( "name[0] = 0x%x \n", name[0] );
	printf( "2 name2[0] = %s \n", name2[0] );

	printf( "name2 = 0x%x \n", name2 );
	printf( "name2[0] = %s \n", name2[0] );
	printf( "name2[1] = %s \n", name2[1] );
	printf( "name2[2] = %s \n", name2[2] );
	printf( "name2[3] = %s \n", name2[3] );
	return 0;
}
