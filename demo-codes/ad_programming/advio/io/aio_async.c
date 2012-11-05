#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void async_read(sigval_t val)
{
	struct aiocb *ptr = 
		(struct aiocb *)val.sival_ptr;
	printf("read=%s", (char *)ptr->aio_buf);	
}

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

	cb.aio_sigevent.sigev_value.sival_ptr = &cb;
	cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
	cb.aio_sigevent.sigev_notify_function = 
		async_read;
	cb.aio_sigevent.sigev_notify_attributes = NULL;	

	ret = aio_read(&cb);
	if (ret == -1) {
		perror("aio_read");
		exit(1);
	}
	
	while (1) {
		sleep(3);
	}

	return 0;
}

