#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
	pid_t pid;

	printf("tid=%d\n", (int)pthread_self());
//	return (void *)123;
	pthread_exit(1234);
}

int main(void)
{
	int ret;
	pthread_t tid;
	void *retptr = NULL;

	ret = pthread_create(&tid, NULL, thread_handler, 
		NULL);
	if (ret != 0) {
		fprintf(stderr, "pthread_create:%s\n", 
			strerror(ret));
		exit(1);	
	}	

	pthread_join(tid, &retptr);
	printf("%d\n", (int)retptr);
	exit(0);
}

