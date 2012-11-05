#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sigpipe_handler(int s)
{
	printf("a broken pipe !\n");
}

int main(void)
{
	int ret, fd[2];
	struct sigaction act;

	act.sa_handler = sigpipe_handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);

	sigaction(SIGPIPE, &act, NULL);

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}

	close(fd[0]);

	ret = write(fd[1], "x", 1);
	if (ret == -1) {
		perror("write");
		exit(1);
	}
	printf("write !\n");
	close(fd[1]);
	exit(0);
}
