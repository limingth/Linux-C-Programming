#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define THREADNUM 5
#define BASE 300000000

pthread_mutex_t lock;
pthread_cond_t cond;

static long long g_prime;

static void prime(void)
{
	long long i;
	int flag = 0;

	for (i = 2; i < g_prime; i++) {
		if (g_prime % i == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		printf("id=%d,%lld is a prime!\n", 
			(int)pthread_self(), g_prime);
	} else if (flag == 1) {
		printf("id=%d,%lld is not a prime!\n", 
			(int)pthread_self(), g_prime);
	}

}

void * thread_handler(void * arg)
{
	while (1) {
		pthread_mutex_lock(&lock);
		pthread_cond_wait(&cond, &lock);
		printf("do prime!\n");
		prime();
		pthread_mutex_unlock(&lock);
	}
}

int main(void)
{
	int i, ret, value;
	pthread_t tid[THREADNUM];
	
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);

	for (i = 0; i < THREADNUM; i++) {
		ret = pthread_create(tid+i, NULL,
			thread_handler, NULL);
		if (ret) {
			fprintf(stderr, "%s\n",
				strerror(ret));
			exit(1);	
		}	
	}

	while (1) {
		printf("Input value:\n");
		scanf("%d", &value);
		
		pthread_mutex_lock(&lock);
		g_prime = BASE + value;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&lock);
	}



}
