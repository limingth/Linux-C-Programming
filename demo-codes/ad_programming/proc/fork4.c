#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	printf("hello world!");

	pid_t pid;

	fflush(NULL);
	pid = fork();

	if (pid == 0) {
		printf("\n");
		exit(0);
	}

	if (pid > 0) {
		printf("\n");
		exit(0);
	}
}
