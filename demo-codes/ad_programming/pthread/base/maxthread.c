#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
	while (1)
		sleep(1);
	return NULL;
}

int main(void)
{
	int i, ret;
	pthread_t tid;

	for (i = 0; i < 10000; i++) {
		ret = pthread_create(&tid, NULL,
			thread_handler, NULL);
		if (ret) {
			fprintf(stderr, 
			"max thread num = %d\n%s\n", 
				i, strerror(ret));
			exit(1);	
		}	
	}
	pthread_exit(NULL);
}
