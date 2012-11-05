#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

int fd[2];

void async_read(int s)
{
	char buf[100];
	int ret;

	ret = read(fd[0], buf, 100);
	printf("read:\n");
	write(1, buf, ret);
	
}

int main(void)
{
	struct sigaction act;
	int ret;

	act.sa_handler = async_read;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	
	sigaction(SIGIO, &act, NULL);

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		return -1;
	}


	ret = fcntl(fd[0], F_GETFL);
	ret |= O_ASYNC;
	
	fcntl(fd[0], F_SETFL, ret); //setting async flag!
	fcntl(fd[0], F_SETOWN, getpid()); // setting owner

	while (1) {
		sleep(rand() % 5 + 5);
		write(fd[1], "hello", 5);
	}

}
