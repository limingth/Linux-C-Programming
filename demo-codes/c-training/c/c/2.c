/*
 *判断输入的数是奇数还是偶数
*/
#include <stdio.h>

int is_odd(int num)
{
    if (num & 0x01) 
        return 1;
    else 
        return 0;
}

int main(int argc, const char *argv[])
{
    int num;
    printf("Please enter a num: ");
    scanf("%d", &num);
    if(is_odd(num))
        printf("%d is odd\n", num);
    else
        printf("%d is even\n", num);
    return 0;
}
