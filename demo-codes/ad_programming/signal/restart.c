#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

void sig_handler(int s)
{

}

int main(void)
{
	struct sigaction act;
	char buf[256];
	int ret;

	act.sa_handler = sig_handler;
	sigemptyset(&act.sa_mask);
	//act.sa_flags = SA_INTERRUPT;
	act.sa_flags = SA_RESTART;

	sigaction(SIGALRM, &act, NULL);
	//signal(SIGALRM, sig_handler);

	alarm(5);

	while (1) {
		ret = read(0, buf, 256);
		if (ret == -1) {
			if (errno == EINTR) {
				perror("read");
				continue;
			}
			exit(1);
		}
		printf("inerrupted!\n");
		write(1, buf, ret);
	}
}
