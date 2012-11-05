/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int * pint;

int a;

int test_int( void )
{
	printf( "<test_int> 1 \n" );

	//pint = (int *)0x588;
	pint = &a;
	printf( "<test_int> 2 \n" );

	*pint = 0x12;
	printf( "<test_int> 3 %d \n", *pint );

	printf( "<test_int> 4 *pint = %d \n", *pint );
	printf( "<test_int> 5 pint = 0x%x \n", pint );
}

char str[10];
char * pstr = "abcdabcdabcd";

int test_str( void )
{
	printf( "<test_str> 1 \n" );
	//pstr = "abcd";
	printf( "<test_str> 2 \n" );

	strcpy( str, "ABCD" );
	printf( "<test_str> 3 \n" );

	//str = "1234";
	//pstr = str;
	printf( "<test_str> 4 \n" );
	
	strcpy( pstr, "AB" );
	printf( "<test_str> 5 \n" );
}

typedef struct student 
{
	//char name[32];
	char * name;
	int age;
} student_t;

void test_struct( void )
{
	int i;
	student_t  zhang;


	printf( "0 zhang's age is %d \n", zhang.age );
	zhang.age = 15;
	printf( "1 zhang's age is %d \n", zhang.age );

	strcpy( zhang.name, "zhangsan" );
	printf( "2 zhang's name copy ok! \n" );
	printf( "3 zhang's name is %s \n", zhang.name );

	strcpy( pstr, zhang.name );
	printf( "4 zhang's name is %s \n", pstr );
	
	return ;

	for( i=0; i<10; i++)
		printf( "0x%x : pstr[%d] = %c 0x%x \n", pstr+i, i, *(pstr+i), *(pstr+i) );

	return;
}

int main( int argc, char * argv[] )
{
//	test_int();

//	test_str();

	test_struct();

	printf( "Hello, Cruel World! \n" );

	return 0;
}
