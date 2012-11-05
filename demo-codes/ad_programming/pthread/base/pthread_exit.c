#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
	pid_t pid;

	printf("tid=%d\n", (int)pthread_self());
//	pthread_exit(NULL);
//	return NULL;
	exit(0);
}

int main(void)
{
	int ret;
	pthread_t tid;

	ret = pthread_create(&tid, NULL, thread_handler, 
		NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create:%s\n", 
			strerror(ret));
		exit(1);	
	}	

//	thread_handler(NULL);
	while (1) {
		sleep(1);
		printf("hello\n");
	}
	pthread_exit(NULL);
}

