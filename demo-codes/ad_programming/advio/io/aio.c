#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	struct aiocb cb;
	char sbuf[100];
	int ret;

	bzero(&cb, sizeof(cb));

	cb.aio_fildes = 0;
	cb.aio_buf = sbuf;
	cb.aio_nbytes = 100;
	cb.aio_offset = 0;

	const struct aiocb * const cblist[2] = {&cb, NULL};
	ret = aio_read(&cb);
	if (ret == -1) {
		perror("aio_read");
		exit(1);
	}
	
	ret = aio_suspend(cblist, 2, NULL);
	if (ret == -1) {
		perror("aio_suspend");
		exit(1);
	}	

	printf("Waitting for aio reading completed!\n");
	while (aio_error(&cb) == EINPROGRESS);
	printf("Read completed!\n");

	ret = aio_return(&cb);
	if (ret > 0) {
		printf("ret=%d, %s", ret, 
			(char *)cb.aio_buf);
	}
	return 0;
}

