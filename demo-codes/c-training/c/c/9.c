/*
 * 输入一行字符，分别统计出其中英文字母，空格，数字和其他字符的个数.
*/

#include <stdio.h>

int str_parse(char *str)
{
    int chars = 0, space = 0, digit = 0, others = 0;
    char tmp;

    while(tmp = *str++)
    {
        if ((tmp >= 'A' && tmp <= 'Z') || (tmp >= 'a' && tmp<= 'z')) 
            chars++;
        else if(tmp >= '0' && tmp <= '9')
            digit++;
        else if(tmp = ' ')
            space++;
        else
            others++;
    }
    printf("%d chars, %d digits, %d space, %d others\n", chars, digit, space, others);
}

int main(int argc, const char *argv[])
{
    char str[100];
    printf("Please enter a string within 100: ");
    fgets(str, 100, stdin);
    str_parse(str);
    return 0;
}
