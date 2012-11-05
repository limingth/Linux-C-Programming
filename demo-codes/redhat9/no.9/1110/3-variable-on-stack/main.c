/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

int * addr = (int *)0;

int test( int para )
{
	int i[1000] ;
//	int i;
	static int j;
	
	printf( "<func> &para = 0x%x \n", &para );
#if 1
	printf( "<func> para = 0x%x \n", para );
	printf( "<func> &i = 0x%x \n", &i );
	printf( "<func> i = 0x%x \n", i );
	printf( "<func> &j = 0x%x \n", &j );
	printf( "<func> j = 0x%x \n", j );
#endif	
	addr = (int *) &i;
	printf( "<func> --- out --- \n" );
	
	test( 5 );
	return 0;
}

int test1( int para )
{
//	int i[1000] ;
	int testi;
	int testj;
	static int j;
	
	printf( "<func1> &para = 0x%x \n", &para );
#if 1
	printf( "<func1> para = 0x%x \n", para );
	printf( "<func1> &testi = 0x%x \n", &testi );
	printf( "<func1> testi = 0x%x \n", testi );
	printf( "<func1> &testj = 0x%x \n", &testj );
	printf( "<func1> testj = 0x%x \n", testj );
	printf( "<func1> &j = 0x%x \n", &j );
	printf( "<func1> j = 0x%x \n", j );
#endif	
//	addr = (int *) &i;
	printf( "<func> --- out --- \n" );
	
	//test( 5 );
	return 0;
}

int main( int argc, char * argv[] )
{
	test( 5 );
	*(int *)(addr) = 0x3344;
	*(int *)(addr-1) = 0x5566;
	test1( 6 );
	return 0;
	test1( 5 );
	return 0;

	//test2( 5, 6, 7, 8, 9 );
	return 0;
}



int test2( int para, int p2, int p3, int p4, int p5 )
{
	int k1 ;
	int k2 ;
	static int jj;
	
	printf( "<func2> &para = 0x%x \n", &para );
	printf( "<func2> para = 0x%x \n", para );
	printf( "<func2> &p2 = 0x%x \n", &p2 );
	printf( "<func2> &p3 = 0x%x \n", &p3 );
	printf( "<func2> &p4 = 0x%x \n", &p4 );
	printf( "<func2> &p5 = 0x%x \n", &p5 );
	printf( "<func2> p2 = 0x%x \n", p2 );
	printf( "<func2> p3 = 0x%x \n", p3 );
	printf( "<func2> p4 = 0x%x \n", p4 );
	printf( "<func2> p5 = 0x%x \n", p5 );

	printf( "<func2> &k1 = 0x%x \n", &k1 );
	printf( "<func2> k1 = 0x%x \n", k1 );

	printf( "<func2> &k2 = 0x%x \n", &k2 );
	printf( "<func2> k2 = 0x%x \n", k2 );

	printf( "<func2> &jj = 0x%x \n", &jj );
	printf( "<func2> jj = 0x%x \n", jj );
	
	//addr = (int *) &i;
	printf( "<func2> --- out --- \n" );
	return 0;
}


