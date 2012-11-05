#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <poll.h>
#include <sys/epoll.h>

int fd[2];


int main(void)
{
	int ret;
	char buf[100];
	struct timeval timeout;
	pid_t pid;
	struct epoll_event pollfds[2], retfds;

	int epfd;

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}
	pollfds[0].data.fd = 0;
	pollfds[0].events = EPOLLIN;
	pollfds[1].data.fd = fd[0];
	pollfds[1].events = EPOLLIN;

	epfd = epoll_create(10);
	if (epfd == -1) {
		perror("epoll_create");
		exit(1);
	}
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, 0,
		&pollfds[0]);
	if (ret == -1) {
		perror("epoll_ctl");
		exit(1);
	}	
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0],
		&pollfds[1]);
	if (ret == -1) {
		perror("epoll_ctl");
		exit(1);
	}

	pid = fork();
	if (pid > 0) {
		close(fd[1]);
		while (1) {
			ret = epoll_wait(epfd, &retfds, 
				1, -1);
			if (ret == -1) {
				perror("epoll_wait");
				exit(1);
			}	
			if (ret == 0) {
				printf("timeout!\n");
			}
			if (ret > 0) {
		           char buf[100];
			   if (retfds.events & 
					EPOLLIN) {
			     ret = read(retfds.data.fd, 
			     	buf, 100);
			     buf[ret-1] = 0;	
			     printf("from fd=%d:%s\n",
			     	retfds.data.fd, buf);	

			    }
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
