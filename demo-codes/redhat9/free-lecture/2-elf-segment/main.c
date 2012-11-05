/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int var1 = 16;
int var2;
int var3 = 1 + 2 * 4;
int var4;
char * var5 = "abcd";
int var6;
const int var7 = 100;
char var8[16] = "ABCD";

int main( int argc, char * argv[] )
{
	printf( "demo elf segment \n" );

	printf( "&var1 = 0x%x \n", &var1 );
	printf( "&var2 = 0x%x \n", &var2 );
	printf( "&var3 = 0x%x \n", &var3 );
	printf( "&var4 = 0x%x \n", &var4 );
	printf( "&var5 = 0x%x \n", &var5 );
	printf( "&var6 = 0x%x \n", &var6 );
	printf( "&var7 = 0x%x \n", &var7 );
	printf( "var8 = 0x%x \n", var8 );
	printf( "var5 = 0x%x \n", var5 );

	return 0; 
}

