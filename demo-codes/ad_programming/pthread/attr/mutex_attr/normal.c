#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lock;

void * test0(void * arg)
{
	pthread_mutex_lock(&lock);
//	pthread_mutex_lock(&lock);

	printf("I am free!\n");
	sleep(3);
	int ret = pthread_mutex_unlock(&lock);
	if (ret)
		printf("%s\n", strerror(ret));

	return NULL;
}

void * test1(void * arg)
{
	sleep(1);

	int ret = pthread_mutex_unlock(&lock);
	if (ret)
		printf("%s\n", strerror(ret));
	printf("try to make 0 free!\n");
	return NULL;
}

int main(void)
{
	int ret;
	pthread_t tid[2];
	pthread_attr_t attr;

	pthread_attr_init(&attr);

	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	pthread_mutex_init(&lock, NULL);



	ret = pthread_create(&tid[0], &attr, 
		test0, NULL);
	if (ret) {
		fprintf(stderr, "create:%s\n", strerror(ret));
		exit(1);
	}

	ret = pthread_create(&tid[0], &attr, 
		test1, NULL);
	if (ret) {
		fprintf(stderr, "create:%s\n", strerror(ret));
		exit(1);
	}	

	pthread_attr_destroy(&attr);

	pthread_exit(NULL);
}
