#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>

int fd[2];

void select_io_work(fd_set * fds)
{
	char buf[100];
	int ret;

	if (FD_ISSET(0, fds)) {
		ret = read(0, buf, 100);
		buf[ret - 1] = '\0';
		printf("read 0: %s\n", buf);
	}
	
	if (FD_ISSET(fd[0], fds)) {
		ret = read(fd[0], buf, 100);
		buf[ret] = '\0';
		printf("read pipe: %s\n", buf);
	}
}

int main(void)
{
	fd_set readfds;
	int ret, nfds;
	char buf[100];
	struct timeval timeout;
	pid_t pid;

	FD_ZERO(&readfds);
	timeout.tv_sec = 300;
	timeout.tv_usec = 0;

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}
	nfds = fd[0] + 1;
	pid = fork();
	if (pid > 0) {
		close(fd[1]);

		while (1) {
			FD_SET(0, &readfds);
			FD_SET(fd[0], &readfds);
			ret = select(nfds, &readfds, 
				NULL, NULL,
				&timeout);
			if (ret == -1) {
				perror("select");
				exit(1);
			}	
			if (ret == 0) {
				printf("timeout!\n");
			}
			if (ret > 0) {
				select_io_work(&readfds);
			}
			timeout.tv_sec = 3000;
			timeout.tv_usec = 0;
		}
	}

	if (pid == 0) {
		close(fd[0]);
		while (1) {
			sleep(rand() % 5 + 3);
			write(fd[1], "hello", 5);
			exit(0);
		}	
	}
}
