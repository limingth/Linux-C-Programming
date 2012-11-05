/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#define N	6

void qsort( int v[], int left, int right )
{
	int i, last;
	void swap( int v[], int i, int j );
	
	if( left >= right )
		return ;

	swap( v, left, (left+right)/2 );

	last = left;

	for( i = left+1; i <= right; i++ )
		if( v[i] < v[left] )
		{
			printf( "last = %d \n", last );
			printf( "    swap( %d, %d ) \n", last+1, i );
			swap( v, ++last, i );
		}

	//printf( "last = %d \n", last );
	swap( v, left, last );
	
	qsort( v, left, last - 1 );
	qsort( v, last+1, right );

	return;
}

void print_array( int v[], int n )
{
	int i;
	static int counter = 0;

	printf( "------------ %d \n", counter++ );
	for( i = 0; i < n; i++ )
	//	printf( "v[%d] = %d \n", i, v[i] );
		printf( "%d ", v[i] );

	printf( "\n" );

	return;
}


void swap( int v[], int i, int j )
{
	int temp;
	if( i==j )	return;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;

	print_array( v, N );
	return;
}

int main( int argc, char * argv[] )
{
	int v[N] = { 5, 1, 4, 3, 6, 2 };

	printf( "hello, Cruel World! \n" );

	print_array( v, 6 );

	qsort( v, 0, 5 );

	print_array( v, 6 );

	return 0; 
}
