#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
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
			fprintf(stderr, "%s\n", 
				strerror(ret));
			exit(1);	
		}	
		pthread_join(tid, NULL);
	}
	exit(0);
}
