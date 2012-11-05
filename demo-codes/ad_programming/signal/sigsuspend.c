#include <stdio.h>
#include <signal.h>

int main(void)
{
	sigset_t mask;
	while (1) {
//		sigsuspend(&mask);
		sigprocmask(SIG_SETMASK, &mask, NULL);
		pause();

		do_work();
	}
}
