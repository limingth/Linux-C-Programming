#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	if (pid == 0) {
	
		printf("I am child my pid is %d"
		  	" and my father pid is %d\n",
			getpid(), getppid());
		exit(0);	
	}

	wait(NULL);

	printf("I am father my pid is %d"
		" and my child is %d\n",
		getpid(), pid);
	exit(0);
}

