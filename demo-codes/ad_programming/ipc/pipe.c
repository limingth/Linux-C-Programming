#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd[2];
	int ret;
	char buf[128];
	pid_t pid;

	ret = pipe(fd);
	if (ret == -1) {
		perror("pipe");
		exit(1);
	}
	
	pid = fork();
	if (pid == -1) {
		perror("fork");
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}

	if (pid == 0) {
		close(fd[1]);
		ret = read(fd[0], buf, 128);
		if (ret == -1) {
			perror("read");
			close(fd[0]);
			exit(1);
		}

		write(1, buf, ret);
		close(fd[0]);
		exit(0);
	}

	if (pid > 0) {
		close(fd[0]);
		ret = write(fd[1], "Hello world!\n", 13);
		if (ret == -1) {
			perror("write");
			close(fd[0]);
			exit(1);
			exit(1);
		}
		close(fd[1]);
		wait(NULL);
		exit(0);
	}
}
