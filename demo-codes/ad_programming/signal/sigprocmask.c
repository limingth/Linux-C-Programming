#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

int main(void)
{
	struct itimerval cur;
	sigset_t mask, oldmask;

	cur.it_value.tv_sec = 3;
	cur.it_value.tv_usec = 0;
	cur.it_interval.tv_sec = 3;
	cur.it_interval.tv_usec = 0;

//	setitimer(ITIMER_REAL, &cur, NULL);

	sigemptyset(&mask);

	sigaddset(&mask, SIGALRM);
	sigaddset(&mask, SIGQUIT);
	sigaddset(&mask, SIGINT);
	

//	sigprocmask(SIG_BLOCK, &mask, &oldmask);
	signal(SIGINT, SIG_IGN);	

	while (1) {
		printf("Hello world!\n");
		sleep(5);
		printf("end!\n");
		signal(SIGINT, SIG_DFL);	
		//sigprocmask(SIG_SETMASK, &oldmask, NULL);
	}
}
