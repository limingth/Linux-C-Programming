/*
 *编程实现对键盘输入的英文句子进行加密，加密方法为，
 当内容为英文字母时其在26字母中的其后三个字母代替该字母，
 若为其它字符则不改变。
*/
#include <stdio.h>

void encode(char *str)
{
    while(*str)
    {
        if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
        {
            *str += 3;
            if(*str > 'z')
                *str -= 26;
            else if(*str > 'Z' && *str < 'a')
                *str -= 26;
        }
        str++;
    }
}

int main(int argc, const char *argv[])
{
    char str[100] = "Where are you going tomorrow?";
    puts(str);
    encode(str);
    puts(str);
    return 0;
}
