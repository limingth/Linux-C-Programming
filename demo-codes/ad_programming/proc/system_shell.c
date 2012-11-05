#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int mysystem(const char *cmd)
{
	int ret;
	pid_t pid;
	int status;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		status = pid;
	} else if (pid == 0) {
		execl("/bin/sh", "sh", "-c", 
			cmd, NULL);
		exit(127);	
	} else {
		waitpid(pid, &status, 0);
	}
	return status;
}

int main(void)
{
	char buf[512];
	int ret;

	while (1) {
		write(1, "%%:", 3);
		ret = read(0, buf, 512);
		if (ret > 0) {
			buf[ret-1] = '\0';
			mysystem(buf);
		}
	}
}
