#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char buf[512];
	int ret;
	pid_t pid;

	while (1) {
		write(1, "%%%(yuanpengjun):", 16);
		ret = read(0, buf, 512);
		if ((ret == 1) && 
			(buf[0] == '\n'))
			continue;
		buf[ret-1] = '\0';	
		pid = fork();
		if (pid == 0)
			execlp(buf, buf, NULL);
		wait(NULL);	

	}
}
