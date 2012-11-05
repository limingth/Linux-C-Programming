#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int s, siginfo_t *info, void *context)
{
	if (info->si_code == SI_QUEUE) {
		printf("Process %d send a value %d\n",
			info->si_pid, 
				info->si_value);
	} else
		printf("caught a unkonw signal!\n");
}

int main(void)
{
	struct sigaction act;

	act.sa_sigaction = sig_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;

	sigaction(SIGUSR1, &act, NULL);

	while (1)
		pause();
			
}
