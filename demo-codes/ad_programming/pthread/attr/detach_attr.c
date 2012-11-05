#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void * thread_handler(void * arg)
{
	pthread_detach(pthread_self());
	while (1)
		sleep(1);
	return NULL;	
}


int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int ret, status;
	
	
	pthread_attr_init(&attr);
	
	pthread_attr_getdetachstate(&attr, &status);
	if (status == PTHREAD_CREATE_DETACHED)
		printf("attribute is detached!\n");
	else if (status == PTHREAD_CREATE_JOINABLE) 
		printf("attribute is joinable!\n");

//	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	ret = pthread_create(&tid, &attr, thread_handler,
		NULL);
	if (ret) {
		fprintf(stderr, "pthread_create:%s",
			strerror(ret));
		exit(1);	
	}	
	sleep(2);	
	ret = pthread_join(tid, NULL);
	printf("pthread_join:%s\n", strerror(ret));
	printf("Main thread exit!pid=%d\n", getpid());
	pthread_exit(NULL);
}
