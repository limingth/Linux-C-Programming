/*
 * 给一个不多于5位的正整数，要求：
 * ①求出它是几位数；
 * ②按逆序打印出各位数字，例如原数是321，应输出123。
*/
#include <stdio.h>

int analyse(int num)
{
    int count = 0, tmp = num;
    while(num)
    {
        count++;
        printf("%d ", num % 10);
        num /= 10;
    }
    printf("\n%d has %d digits\n", tmp, count);
}

int main(int argc, const char *argv[])
{
    int num;
    printf("Please enter a integer < 100000: ");
    scanf("%d", &num);
    analyse(num);
    return 0;
}
