#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

void async_read(int s)
{
	char buf[100];
	int ret;

	ret = read(0, buf, 100);
	printf("read:\n");
	write(1, buf, ret);
	
}

int main(void)
{
	struct sigaction act;
	int ret;

	act.sa_handler = async_read;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	
	sigaction(SIGIO, &act, NULL);

	ret = fcntl(0, F_GETFL);
	ret |= O_ASYNC;
	
	fcntl(0, F_SETFL, ret); //setting async flag!
	fcntl(0, F_SETOWN, getpid()); // setting owner

	while (1) {
		sleep(1);
	}

}
