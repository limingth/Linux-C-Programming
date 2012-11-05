/*
 * 不使用第三个变量，交换两个变量的值
*/
#include <stdio.h>

int main(int argc, const char *argv[])
{
    int a = 5, b = 6;
    printf("a = %d, b = %d\n", a, b);
    a = a + b;
    b = a - b;
    a = a - b;
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
