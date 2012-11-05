#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>

#define BUFSIZE 5

void alarm_handler(int s)
{

}

int main(int argc, char **argv)
{
	if (argc != 2)
		return -1;

	int fd, ret;
	char buf[BUFSIZE];
	struct itimerval cur;

	cur.it_value.tv_sec = 5;
	cur.it_value.tv_usec = 0;
	cur.it_interval.tv_sec = 0;
	cur.it_interval.tv_usec = 50000;

	signal(SIGALRM, alarm_handler);

	setitimer(ITIMER_REAL, &cur, NULL);

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	while (1) {
		pause();
		ret = read(fd, buf, BUFSIZE);
		if (ret == 0)
			break;
		write(1, buf, ret);	
	}
	
	close(fd);
	exit(0);
}
