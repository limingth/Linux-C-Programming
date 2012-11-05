#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>

int fd[2];

void select_io_work(struct pollfd * fds)
{
	char buf[100];
	int ret;

	if (fds[0].revents & POLLIN) {
		ret = read(fds[0].fd, buf, 100);
		buf[ret - 1] = '\0';
		printf("read 0: %s\n", buf);
	}
	
	if (fds[1].revents & POLLIN) {
		ret = read(fds[1].fd, buf, 100);
		buf[ret] = '\0';
		printf("read pipe: %s\n", buf);
	}
}

int main(void)
{
	int ret;
	char buf[100];
	struct timeval timeout;
	pid_t pid;
	struct pollfd pollfds[2];

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}
	pollfds[0].fd = 0;
	pollfds[0].events = POLLIN;
	pollfds[1].fd = fd[0];
	pollfds[1].events = POLLIN;


	pid = fork();
	if (pid > 0) {
		close(fd[1]);
		while (1) {
			ret = poll(pollfds, 2, -1);
			if (ret == -1) {
				perror("poll");
				exit(1);
			}	
			if (ret == 0) {
				printf("timeout!\n");
			}
			if (ret > 0) {
				select_io_work(pollfds);
			}
		}
	}

	if (pid == 0) {
		close(fd[0]);
		while (1) {
			sleep(rand() % 5 + 3);
			write(fd[1], "hello", 5);
			//exit(0);
		}	
	}
}
