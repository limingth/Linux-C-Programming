#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void * thread_handler(void * arg)
{
	int ret = 9;
	char * ptr = (char *)(arg+8192);
	printf("ret's addr = %p, %c\n", &ret, *ptr);

	return NULL;	
}


int main(void)
{
	pthread_t tid;
	pthread_attr_t attr;
	int ret, status;
	void * stackaddr = NULL;
	size_t stacksize;
	
	stackaddr = malloc(16384);
	stacksize = 16384;

	char * ptr = (char *)(stackaddr + 8192);
	*ptr = 'c';
	pthread_attr_init(&attr);

	ret = pthread_attr_setstack(&attr, stackaddr, stacksize);
	if (ret)
		fprintf(stderr, "set stack:%s\n", strerror(ret));
	ret = pthread_create(&tid, &attr, thread_handler,
		stackaddr);
	if (ret) {
		fprintf(stderr, "pthread_create:%s",
			strerror(ret));
		exit(1);	
	}	
	ret = pthread_join(tid, NULL);
	printf("pthread_join:%s\n", strerror(ret));
	pthread_exit(NULL);
}
