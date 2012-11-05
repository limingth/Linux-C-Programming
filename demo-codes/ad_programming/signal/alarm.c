#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef void(*task)(void);

task g_task;
static int cnt;


void task1(void)
{
	printf("task1 has schedued!\n");
}

void task2(void)
{
	printf("task2 has schedued!\n");
}
void sig_handler(int s)
{
	cnt++;
	if (cnt == 1)
		g_task = task1;
	else if (cnt == 2)
		g_task = task2;
	g_task();	
	
}

int main(void)
{
	signal(SIGALRM, sig_handler);
	alarm(5);
	sleep(2);
	pid_t pid = fork();
	if (pid == 0) {
		int ret = alarm(8);
		printf("ret=%d\n", ret);
	}
	while (1)
		sleep(1);
}
