/*   this file is to be used in ucosII on SkyEye like <stdio.h> in linux */


// #define NULL 0

/*  Function for public use */
void skyeye_putc( char ch );
void skyeye_puts( char * s );
void skyeye_printf( char* ctrl, ...);

char skyeye_getc( void );
char * skyeye_gets ( char * s );

