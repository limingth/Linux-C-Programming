#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
	pid_t pid;
/*
	pid = fork();
	if (pid == 0) {
		printf("my pid = %d\n", getpid());
		while (1)
			sleep(1);
	}
*/

	write(1, "Hello", 5);
//	printf("asdftid=%d\n", (int)pthread_self());
//	printf("tid=%d\n", (int)pthread_self());
	return NULL;
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

	usleep(2);
	exit(0);
}

