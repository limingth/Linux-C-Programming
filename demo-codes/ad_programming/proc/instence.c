#include <stdio.h>
#include <stdlib.h>

void data_process(char * buf)
{
	sleep(10); // data is processing!
	printf("Data is processed!\n");
	return;
}

int main(void)
{
	char buf[100];
	int ret;
	pid_t pid;

	while (1) {
		printf("%$$$:");
		fflush(stdout);
		ret = read(0, buf, 100);
		pid = fork();
		if (pid == -1) {
			perror("read");
			exit(1);
		}
		if (pid == 0) {
			data_process(buf);
			exit(0);
		}
	}
}
