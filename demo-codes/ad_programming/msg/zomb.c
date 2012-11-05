#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

int destory_child()
{
	struct sigaction sig;
	sig.sa_handler = SIG_IGN;
	sigemptyset(&(sig.sa_mask));
	sig.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &sig, NULL);
}

int main(int argc, const char *argv[])
{
	pid_t pid;

	destory_child();
	pid = fork();
	if(pid == 0)
	{
		exit(0);
	}

	if(pid > 0)
	{
		sleep(15);
	}

	return 0;
}
