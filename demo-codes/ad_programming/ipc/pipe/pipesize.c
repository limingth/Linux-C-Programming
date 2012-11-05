#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int cnt;
void alarm_handler(int s)
{
	printf("pipe max size is %d\n", cnt);
}

int main(void)
{
	int ret;
	int fd[2];
	struct sigaction act;

	act.sa_handler = alarm_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;

	sigaction(SIGALRM, &act, NULL);


	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}

	while (1) {
		ret = write(fd[1], "x", 1);
		cnt += ret;
		alarm(1);
	}

}
