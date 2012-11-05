#include <stdio.h>

int main(void)
{
	char buf[100];
	int i = 0;

	printf("hello, del space demo\n");
	printf("please input: \n");
	gets(buf);

	printf("S: <%s>\n", buf);
	printf("O: <");

	i = 0;
	while (buf[i])
	{
		if (i == 0)
		{
			printf("%c", buf[i]);
			i++;
			continue;
		}

		if (buf[i] == ' ' && buf[i-1] == ' ')
		{
			i++;
			continue;
		}

		printf("%c", buf[i]);
		i++;
	}
	
	printf(">\n");
	return 0;
}
