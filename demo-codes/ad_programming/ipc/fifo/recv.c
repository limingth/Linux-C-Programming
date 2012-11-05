#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define COMMUDOT "./cdot"

int recvData(char * buf, int size)
{
	int fd, ret;

	fd = open(COMMUDOT, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return fd;
	}
	printf("recv:open\n");
	ret = read(fd, buf, size);
	if (ret == -1) {
		perror("read");
		return ret;
	}

	close(fd);
	return 0;
}

int main(void)
{
	char buf[256];
	int ret;
	
	ret = recvData(buf, 256);
	if (ret == 0)
		printf("%s", buf);
	return 0;
}
