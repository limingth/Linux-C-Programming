#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler(int s)
{
	printf("pid=%d got a signal!\n", getpid());
//	sleep(5);
}

int main(void)
{
	signal(SIGINT, sig_handler);

//	sleep(3);

	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		signal(SIGINT, SIG_DFL);
		while (1)
			sleep(1);
		exit(0);	
	}
	if (pid > 0) {
		while (1)
			sleep(1);
		exit(0);	
	}
}
