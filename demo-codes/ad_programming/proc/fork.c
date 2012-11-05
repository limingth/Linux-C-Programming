#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	goto H2;
H1:
	printf("Child test\n");
	exit(0);
H2:	
	printf("Hello I am father %d\n", getpid());
	pid_t pid = fork();
	if (pid == 0) {
		printf("I am child\n");
		goto H1;
		exit(0);
	}
	sleep(1);

	if (pid > 0) {
		printf("I am father\n");
	}

	printf("Hello I am %d, and my father is %d\n", 
		getpid(), getppid());

	if (pid > 0)
		wait(NULL);
	return 0;
}
