#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	int i;

	pid_t pid;

	for (i = 0; i < 10000; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) 
			exit(0);
		wait(NULL);	
	}
	exit(0);
}
