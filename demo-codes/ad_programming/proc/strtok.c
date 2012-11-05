#include <stdio.h>
#include <string.h>

int main(void)
{
	char buf[] = "ls *&& -a *&&&        -l";
	char *delim = " *&";
	char *retptr = NULL;
	char *str = buf;
	int cnt, i = 0;
	
	cnt = strlen(buf);
	printf("%s\n", buf);
	while (1) {
		retptr = strtok(str, delim);
		if (retptr)
			printf("%s\n", retptr);
		else
			break;
		str = NULL;	
	}

	while (1) {

		printf("%c", buf[i]);
		i++;
		if (i == cnt)
			break;
	}
	printf("\n");
	return 0;
}
