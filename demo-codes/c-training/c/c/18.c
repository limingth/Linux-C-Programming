#include <stdio.h>
#include <string.h>

int max_substring(char *str)
{
    int max = 0, i = 0;
    while(*str)
    {
        if (*str == ' ') 
        {
            if (max <= i) 
                max = i;
            i = 0;
        }
        else
            i++;
        str++;
    }
    if(max <= i)
        max = i;
    return max;
}

int main(int argc, const char *argv[])
{
    char str[100];
    int max_length = 0;
    printf("Please enter a string: ");
    fgets(str, 100, stdin);
    str[strlen(str) - 1] = '\0'; //fgets will receive the '\n' at the end,clear it
    max_length = max_substring(str);

    printf("The longest length is %d.\n", max_length);
    
    return 0;
}
