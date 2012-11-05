/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>

#if 1
struct point 
{
	int x;
	int y;
	char str[10];
};
#endif

struct point makepoint2( struct point b )
{
	struct point temp;
	
	temp.x = b.x;
	temp.y = b.y;

	b.x = 0;
	b.y = 0;

	printf( "b.str = %s \n", b.str );

	printf( "<func> addr(x,y) = (0x%x, 0x%x) \n", &(temp.x), &(temp.y) );
	return temp;
}

struct point makepoint( int x, int y )
{
	struct point temp;
	
	temp.x = x;
	temp.y = y;

	strcpy( temp.str, "12345" );

	printf( "<func> addr(x,y) = (0x%x, 0x%x) \n", &(temp.x), &(temp.y) );
	return temp;
}


struct point dsize( struct point temp )
{
	printf( "<dsize> : temp point pos = (%d, %d) \n", temp.x, temp.y );
	temp.x = temp.x * 2;
	temp.y = temp.y * 2;

	printf( "<dsize> addr(x,y) = (0x%x, 0x%x) \n", &(temp.x), &(temp.y) );
	return temp;
}

struct point a;
struct point b = { 16, 17, "aabbccdd" };


char ss[10];
int main( int argc, char * argv[] )
{
	printf( "hello, Cruel World! \n" );

	printf( "1: a point pos = (%d, %d) \n", a.x, a.y );
	printf( "1: a.str = %s \n", a.str );

	printf( "1: b point pos = (%d, %d) \n", b.x, b.y );
	printf( "1: b.str = %s \n", b.str );

#if 0
	printf( "<main 1> addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );
	a = makepoint( 1, 2 );

	printf( "2: point pos = (%d, %d) \n", a.x, a.y );
	printf( "2: a.str = %s \n", a.str );

	printf( "<main 2> addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );
	//return 0;
#endif	
	printf( "---- dsize ----- \n" );
#if 0
	printf( "-> addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );
	dsize( a );

	printf( "1: point pos = (%d, %d) \n", a.x, a.y );
	printf( "after -> addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );
	
	//return 0;

	a = dsize( a );
	printf( "2: point pos = (%d, %d) \n", a.x, a.y );
	printf( "addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );
	//return 0;
#endif

	printf( "---- assign ----- \n" );
#if 0
	a = b;
	printf( "2: point pos = (%d, %d) \n", a.x, a.y );
	printf( "2: a.str = %s \n", a.str );
	
	return 0;
#endif 

	a.x = b.x;
	a.y = b.y;
	strcpy( a.str, b.str );
	printf( "3: point pos = (%d, %d) \n", a.x, a.y );
	printf( "3: a.str = %s \n", a.str );
	
	//printf( "addr(x,y) = (0x%x, 0x%x) \n", &(a.x), &(a.y) );

	return 0;
}


