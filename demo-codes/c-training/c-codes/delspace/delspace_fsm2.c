#include <stdio.h>

int main(void)
{
	char buf[100];
	int i = 0;
	int state = 0;

	printf("hello, del space demo\n");
	printf("please input: \n");
	gets(buf);

	printf("S: <%s>\n", buf);
	printf("O: <");

	state = 0;
	while (buf[i])
	{
		if (buf[i] != ' ')
		{
			state = 0;
			printf("%c", buf[i]);
		}

		if (state == 0 && buf[i] == ' ')
		{
			state = 1;
			printf("%c", buf[i]);
		}			
		i++;
	}
	
	printf(">\n");
	return 0;
}
