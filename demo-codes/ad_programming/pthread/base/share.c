#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int g_value = 9;
int * g_ptr;

void * thread_handler(void * arg)
{
	g_value++;
	int local = 8;
	g_ptr = &local;
	int *ptr = (int *)arg;
	(*ptr)++;

	while (1) {
		sleep(1);
		printf("local=%d\n", local);
	}	
	return NULL;
}

int main(void)
{
	int ret;
	pthread_t tid;
	void * retPtr;

	int * arg = (int *)malloc(sizeof(int));
	*arg = 9;

	int local = 9;

	ret = pthread_create(&tid, NULL, 
		thread_handler, (void *)&local);
	if (ret) {
		fprintf(stderr, "pthread_create:%s",
			strerror(ret));
		exit(1);	
	}	

	while (1) {
		sleep(1);
		*g_ptr += 1;
	}
	pthread_join(tid, NULL);
	
	printf("local = %d\n", local);

	free(arg);
	pthread_exit(NULL);
}
