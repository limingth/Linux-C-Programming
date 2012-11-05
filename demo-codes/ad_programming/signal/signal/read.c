#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void alarm_handler(int s)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
		printf("Alarm!\n");
}

int main(void)
{
	char buf[512];
	int ret;
	signal(SIGALRM, alarm_handler);

	while (1) {
		ret = read(0, buf, 512);
		buf[ret-1] = '\0';
		printf("hi:%s\n", buf);
		alarm(atoi(buf));
	}
}
