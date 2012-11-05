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
		close(fd[0]);
		dup2(fd[1], 1);

		execlp("ls", "ls", "-al", NULL);
		
		close(fd[1]);
		exit(0);
	}

	if (pid > 0) {
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
		//execlp("grep", "grep", "r", NULL);
		execlp("md5sum", "md5sum", NULL);

		close(fd[1]);
		exit(0);
	}
}
