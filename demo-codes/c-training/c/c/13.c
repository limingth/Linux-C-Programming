/*
 *判断三个值能否组成三角形
 */
#include <stdio.h>

int is_triangle(int a, int b, int c)
{
    int result = 0;

    if (a + b > c &&
        a + c > b &&
        b + c > a) 
    {
        result = 1;
    }
    return result;
}

int main(int argc, const char *argv[])
{
    int a, b, c;
    printf("Please enter 3 integer: ");
    scanf("%d %d %d", &a, &b, &c);

    if(is_triangle(a, b, c))
        printf("YES\n");
    else
        printf("NO\n");
    return 0;
}
