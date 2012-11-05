#include <aio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void async_read(int s, siginfo_t * info, void * context)
{
	struct aiocb *ptr = 
		(struct aiocb *)info->si_value.sival_ptr;
	printf("read=%s", (char *)ptr->aio_buf);	
}

int main(void)
{
	struct aiocb cb;
	char sbuf[100];
	int ret;
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	act.sa_sigaction = async_read;

	sigaction(SIGUSR1, &act, NULL);

	bzero(&cb, sizeof(cb));

	cb.aio_fildes = 0;
	cb.aio_buf = sbuf;
	cb.aio_nbytes = 100;
	cb.aio_offset = 0;

	cb.aio_sigevent.sigev_value.sival_ptr = &cb;
	cb.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	cb.aio_sigevent.sigev_signo = SIGUSR1;
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

