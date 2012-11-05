#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t lock;
int g_val0, g_val1;

int func(void)
{
	int ret, val;
	ret = pthread_mutex_lock(&lock);
	if (ret)
		printf("func:lock:%s\n", strerror(ret));
	val = g_val1+8;
#if 0
	ret = pthread_mutex_unlock(&lock);
	if (ret)
		printf("func:unlock%s\n", strerror(ret));
#endif
	return val;
}

void * test0(void * arg)
{
	int ret;

	ret = pthread_mutex_lock(&lock);
	if (ret)
		printf("lock:%s\n", strerror(ret));
	
	sleep(5);
	g_val0 = func();
	printf("res=%d\n", g_val0);
	ret = pthread_mutex_unlock(&lock);
	if (ret)
		printf("unlock%s\n", strerror(ret));

	return NULL;
}

void * test1(void * arg)
{
	sleep(1);

#if 1
	int ret = pthread_mutex_lock(&lock);
	if (ret)
		printf("1:%s\n", strerror(ret));
	printf("g_val0=%d\n", g_val0);
	
	ret = pthread_mutex_unlock(&lock);
	if (ret)
		printf("1:unlock%s\n", strerror(ret));
#endif
	return NULL;
}

int main(void)
{
	int ret;
	pthread_t tid[2];
	pthread_attr_t attr;
	pthread_mutexattr_t mutexattr;

	pthread_attr_init(&attr);
	pthread_mutexattr_init(&mutexattr);

	pthread_attr_setdetachstate(&attr, 
		PTHREAD_CREATE_DETACHED);
	pthread_mutexattr_settype(&mutexattr,
		PTHREAD_MUTEX_RECURSIVE_NP);
	
	pthread_mutex_init(&lock, &mutexattr);
	pthread_mutexattr_destroy(&mutexattr);



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
