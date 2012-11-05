#include "head.h"
#include <string.h>

int main(void)
{
	PIPE * pipe = NULL;
	int ret;
	pid_t pid;

	ret = createPipe(&pipe);
	if (ret == -1) {
		printf("create fail!\n");
		return -1;
	}

	pid = fork();
	if (pid == 0) {
		setRDWRflag(pipe, WRITE);
		ret = writePipe(pipe, "Hello world!\n", 
			13);
		if (ret == -1) {
			printf("write pipe fail!\n");
			closePipe(pipe);
			exit(1);
		}	
		closePipe(pipe);
		exit(0);
	}

	if (pid > 0) {
		wait(NULL);
		setRDWRflag(pipe, READ);
		char buf[32];
		bzero(buf, 32);
		ret = readPipe(pipe, buf, 13);
		if (ret == -1) {
			printf("read pipe fail!\n");
			closePipe(pipe);
			exit(1);
		}
		printf("%s", buf);
		closePipe(pipe);
		exit(0);
	}
}
