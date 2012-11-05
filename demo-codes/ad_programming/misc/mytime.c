#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/times.h>

int main(int argc, char **argv)
{

	long long clk;
	pid_t pid;
	clock_t start, end;
	struct tms wstart, wend;

	clk = sysconf(_SC_CLK_TCK);

	start = times(&wstart);
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		execvp(argv[1], &argv[1]);
		perror("execvp");
		exit(1);
	}

	waitpid(pid, NULL, 0);
	end = times(&wend);

	printf("real:\t%7.3f\n", (end-start)/(double)clk);
	printf("user:\t%7.3f\n", 
		(wend.tms_cutime-wstart.tms_cutime) /
			(double)clk);
	printf("system:\t%7.3f\n", 
		(wend.tms_cstime-wstart.tms_cstime) /
			(double)clk);

	return 0;
}
