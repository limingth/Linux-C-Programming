#include <stdio.h>

int atoi(const char *str)
{
        int i = 0;
        int ret = 0;

        while (str[i]) 
        { 
            ret = ret * 10 + (str[i] - '0');
            i++;
        }
       
        return ret;
}

char * itoa(int num, char * str)
{
        int i = 0;
        int len = 0;
        char tmp;

        do
        {
            str[i] = num % 10 + '0';
            num = num / 10;
            i++;
        } while (num);

        str[i] = '\0';
        len = i;

        // reverse string
        for (i = 0; i < len/2; i++)
        {
                tmp = str[i];
                str[i] = str[len-1-i];
                str[len-1-i] = tmp;
        }

        return str;
}

int main(void)
{
	char str[4] = "123";
	int result;
	char str2[32];

	printf("hello, demo atoi \n");

	printf("123 -> %d \n", atoi("123"));
	result = atoi(str);
	printf("123 -> %d \n", result);

	printf("123 : %s \n", itoa(123, str2));
	itoa(0, str2);
	printf("0 : %s \n", str2);

	return 0;
}
