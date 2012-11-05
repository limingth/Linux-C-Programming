#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define COMMUDOT "./cdot"

int sendData(const char * buf)
{
	int fd, ret;

	fd = open(COMMUDOT, O_WRONLY);
	if (fd == -1) {
		perror("open");
		return fd;
	}

	printf("open sucess!\n");
	ret = write(fd, buf, strlen(buf));
	if (ret == -1) {
		perror("write");
		return ret;
	}

	close(fd);
	return 0;
}

int main(void)
{
	sendData("hello world!\n");

	return 0;
}
