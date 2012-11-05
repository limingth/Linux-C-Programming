/*
 *  编写函数char *mystrcpy(char *dest, char *src);
 *  实现strcpy的功能。
*/

#include <stdio.h>

char *mystrcpy(char *dest, char *src)
{
    char *tmp = src;
    while(*dest++ = *src++);
    return tmp;
}

int main(int argc, const char *argv[])
{
    char *src = "Hello world!";
    char dest[100];

    printf("%s\n", src);
    mystrcpy(dest, src);
    printf("%s\n", dest);

    return 0;
}
