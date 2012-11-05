/*
 *编程实现将任意的十进制整数转换为R进制数（R在2-16之间）
*/
#include <stdio.h>

int convert(int num, int R)
{
    char *str = "0123456789ABCDEF";
    int a[16] = {0};
    int i = 0;
    if (num < 0) 
    {
        putchar('-');
        num = -num;
    }

    while(num)
    {
        a[i++] = num % R;
        num = num / R;
    }

    while(i-- >0)
        putchar(str[a[i]]);
}

int main(int argc, const char *argv[])
{
    int num, R;
    printf("Please enter an integer: ");
    scanf("%d", &num);
    printf("Please intput R: ");
    scanf("%d", &R);

    convert(num, R);
    printf("\n");
    return 0;
}
