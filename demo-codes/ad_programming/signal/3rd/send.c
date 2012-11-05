#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
		return -1;
	}

	pid_t pid = atoi(argv[1]);
	union sigval val;

	val.sival_int = atoi(argv[2]);

	int ret = sigqueue(pid, SIGUSR1, val);
	if (ret == -1) {
		perror("sigqueue");
		exit(1);
	}
	exit(0);
}
