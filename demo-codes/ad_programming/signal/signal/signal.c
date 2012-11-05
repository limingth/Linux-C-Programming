#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

static int sigint_cnt;
static int sigquit_cnt;

void signal_handler(int s)
{
	int cnt;
	printf("signal %d was catched!\n", s);
	if (s == SIGINT)
		cnt = ++sigint_cnt;
	else if (s == SIGQUIT)
		cnt = ++sigquit_cnt;
	sleep(5);
	
	printf("signal sigint occur times=%d\n", cnt);
}

int main(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1) {
//		printf("Hello world!\n");
		sleep(1);
	}

	return 0;
}
