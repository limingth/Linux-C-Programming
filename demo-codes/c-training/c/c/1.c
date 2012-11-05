/*
 *使用for循环从1加到100，并输出结果。
*/ 

#include <stdio.h>

int main(int argc, const char *argv[])
{
    int i, result = 0;

    for (i = 1; i <= 100; i++) 
    {
        result += i;
    }

    printf("result = %d\n", result);

    return 0;
}
