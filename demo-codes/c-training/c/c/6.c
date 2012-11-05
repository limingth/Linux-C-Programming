/*
 * 有三个整数a,b,c，由键盘输入，输出其中最大的数。
*/ 
#include <stdio.h>

int get_max(int a, int b, int c)
{
    if (a < b) 
        a = b;
    if (a > c) 
        return a;
    else
        return c;
}

int main(int argc, const char *argv[])
{
    int a, b, c, max;
    scanf("%d,%d,%d", &a, &b, &c);
    max = get_max(a, b, c);
    printf("max = %d\n", max);
    return 0;
}
