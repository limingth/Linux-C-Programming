#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNUM 10

int main(void)
{
	int i = 0;
	pid_t pid;
	struct sigaction act;

	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;

	sigaction(SIGCHLD, &act, NULL);

	for (i = 0; i < MAXNUM; i++) {
		pid = fork();
		if (pid == 0)
			exit(0);
		if (pid == -1) {
			perror("fork");
			exit(1);
		}	
	}

	while (1)
		sleep(1);
}
