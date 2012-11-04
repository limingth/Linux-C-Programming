#include <stdio.h>

#define N 1024

char *my_strcpy(char *dest, char *src)
{
    int i;
    for(i = 0; src[i]; ++i)
	   dest[i] = src[i];
    
     dest[i] = '\0';
    return dest;
}

int main(int argc, char *argv[])
{
    char d[N];
    char s[N] = "Hello World";

    printf("s = %s\n", s);
//    my_strcpy(d, s);
    printf("d = %s\n", my_strcpy(d,s));
    return 0;
}

