#include <stdio.h>

int main(void)
{
	int num;
	int div, rest;
	char str[100];
	int i = 0;
	int tmp, len;
	int sum = 0;

	printf("hello, akaer demo \n");
	printf("please input a number: ");

	scanf("%d", &num);
	printf("your number is %d\n", num);

	div = num;
	i = 0;
	while(div != 0)
	{
		rest = div % 2;
		div = div / 2;
		//printf("div = %d, rest = %d \n", div, rest);
		str[i] = rest + '0';
		//printf("str[i] = %c \n", str[i]);
		i++;
	}
	str[i] = '\0';
	printf("str = %s \n", str);

	len = i;
	printf("len = %d \n", len);
	/* reverse string , like "hello" -> "olleh" */	
	for(i = 0; i < len/2; i++)
	{
		tmp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = tmp;
	}
	printf("reverse str = %s \n", str);

	sum = 0;
	/* summary how many 1 in this numer */
	for(i = 0; i < len; i++)
	{
		if(str[i] == '1')
			sum++;
	}
	printf("sum = %d \n", sum);

	return 0;
}
