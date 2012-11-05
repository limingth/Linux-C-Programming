#include <stdio.h>

void pkgtest()
{
    fprintf(stderr, "This is a test!\n");
}

int int_char( char ch)
{
    fprintf(stderr, "int_char input charactor:%c\n", ch);
    
    return 100;
}

char char_float( float f )
{
    fprintf(stderr, "char_float input float: %f\n", f);
    
    return 'A';
}

char* string_void()
{
	char* str;
	int len;

	len = strlen("test");
	str = (char*)malloc( len + 1 );

	strcpy(str, "test");
	str[len] = '\0';

	return str;
}
