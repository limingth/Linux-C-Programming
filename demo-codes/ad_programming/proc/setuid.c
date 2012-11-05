#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	int fd;
	char buf[20];

	printf("My real id is %d and my"
		" effective id is %d \n",
			getuid(), geteuid());
	fd = open("/home/yuanpengjun/ad_programming/"
			"proc/tmp", 
		O_RDWR | O_APPEND);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	write(fd, " hello world", 11);
	close(fd);
	exit(0);
}
