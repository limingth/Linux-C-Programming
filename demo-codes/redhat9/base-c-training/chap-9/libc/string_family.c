/*
 *      main.c - demo helloworld application
 *
 *	Author: li ming <limingth@akaedu.org>
 *	Date:	2007-01-01
 *	Version:  1.0
 */

#include <stdio.h>
#include <assert.h>

#define	printh( hint, str )	\
printf( hint " -> " #str " = \"%s\" \n", str )

#define	printd( op, str )	printf( #op " -> " #str " = %d \n", str )

#define	prints( op, str )	\
printf( #op " -> " #str " = %s \n", str )

#define	print( op )		printf( #op " -> " #op " = \"%s\" \n", op )

mystrcpy( char * src, char * dst )
{
	assert( src );

}

int main( int argc, char * argv[] )
{
	char src[64];
	char dst[64];
	int ret;
	char * p = src ;
	int i;

	printf( "hello, Cruel World! \n" );

	strcpy( src, "hello" );
	strcpy( dst, "123456789" );

#if 1	
	printf( "strcpy(src,\"hello\") -> src = \"%s\" \n", src );
	printf( "strcpy(dst,\"123456789\") -> dst = \"%s\" \n", dst );
//	return 0;
#endif 

	printh( "strcpy( src, \"hello\" );", src );
	printh( "strcpy( dst, \"123456789\" );", dst );
	//return 0;

	//print( strcpy( src, "abcd" ) );
	//print( strcpy( dst, "1234" ) );
	//return 0;

	prints( strcpy( src, "hello" );, src );
	prints( strcpy( dst, "123454678" );, dst );

	strncpy( dst, "world!", 6 );
	prints( strncpy( dst, "world!", 6 );, dst );

	strcat( dst, src );
	prints( strcat( dst, src );, dst );

	strncat( dst, src, 5 );
	prints( strncat( dst, src, 5 );, dst );

	if( strcmp( src, "hello" ) == 0 )
		prints( strcmp( src, "hello" ) == 0, src );
	else
		prints( strcmp( src, "hello" ) != 0, src );
	
	if( strcmp( dst, "world!789hellohello" ) == 0 )
		prints( strcmp( dst, "world!789hellohello" ) == 0, dst );
	else
		prints( strcmp( dst, "hello" ) != 0, dst );
		
	prints( strchr( dst, 'A' ), dst );
	print( strchr( dst, 'A' ) );

	print( strrchr( dst, 'B' ) );

	printd( strspn( dst, "worlf" ), strspn( dst, "worlf" ) );
	printd( strcspn( dst, "aorlf" ), strcspn( dst, "abraa" ) );

	print( strpbrk( dst, "e9" ) );

	print( strstr( dst, "789" ) );

	printd( strstr( dst, "ld" ), strstr( dst, "ld" ) - dst );
	printd( strlen( dst ), strlen( dst ) );

#if 0
	for( i=0; i<1000; i++ )
		printf( " %d %s \n", i, strerror( i ) );

	print( strtok( dst, "!9" ) );
	for( i=0; i<20; i++ )
		printf( "dst[%d] = %c \n", i, dst[i] );	

	print( strtok( dst, "!9" ) );
	for( i=0; i<20; i++ )
		printf( "dst[%d] = %c \n", i, dst[i] );	

#endif
	assert( p );
	return 0;
}
