#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == 0) {
		sleep(5);
		exit(0);
	}
	waitpid(-1, NULL, 0);
	printf("Wait!\n");
	exit(0);
	if (pid == 0)
		exit(0);
	if (pid > 0) {
		exit(0);
		while (1) {
			wait(NULL);
			sleep(1);
		}
	}	
}
