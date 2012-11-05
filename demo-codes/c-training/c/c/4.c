/*
 * 用switch语句实现加减乘除
*/
#include <stdio.h>

int calc(int a, int b, char c)
{
    switch(c)
    {
        case '+' :  return a + b; break;
        case '-' :  return a - b; break;
        case '*' :  return a * b; break;
        case '/' :  return a / b; break;
        default : break;
    }
}

int main(int argc, const char *argv[])
{
    int a, b, result;
    char c;
    scanf("%d,%c,%d", &a, &c, &b);
    result = calc(a, b, c);
    printf("result = %d\n", result);
    return 0;
}
