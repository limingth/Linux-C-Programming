#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("/etc/passwd", O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	pid_t pid;

	pid = fork();

	if (pid > 0) {
		close(fd);
		char buf[20];
		read(fd, buf, 20);
		/*
		int ret = read(fd, buf, 20);
		if (ret == -1) {
			perror("read");
			exit(1);
		}
		*/
		write(1, "This is father:\n", 16);
		write(1, buf, 20);
		write(1, "\n", 1);
		close(fd);
		exit(0);
	}

	if (pid == 0) {
		sleep(2);
		char buf[20];
		int ret = read(fd, buf, 20);
		if (ret == -1) {
			perror("read");
			exit(1);
		}
		write(1, "This is child:\n", 15);
		write(1, buf, ret);
		write(1, "\n", 1);
		close(fd);
		exit(0);
	}
}
