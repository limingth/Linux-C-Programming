#include <stdio.h>
#include <signal.h>

void sig_handler(int s)
{
	printf("%s was catched!\n");
}

int main(void)
{
	//signal(SIGKILL, SIG_IGN);
	signal(SIGKILL, sig_handler);
	signal(SIGSTOP, SIG_IGN);

	while (1) {
		sleep(1);
		printf("Hello world!\n");
	}
		
}
