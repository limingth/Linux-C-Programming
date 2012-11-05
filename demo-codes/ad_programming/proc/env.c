#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

int main(void)
{
	int i = 0;

	environ[28] = "HOME=/home/yuanchonghuan";
	while (environ[i]) {
		printf("%s\n", environ[i]);

		if (strncmp(environ[i], "HOME", 4) == 0)
			printf("i=%d\n", i);
		i++;
	}	
	exit(0);
}
