#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

void testTime(struct timeval *priv, struct timeval *next)
{
	long long sec, usec, consume;
	sec = next->tv_sec - priv->tv_sec;
	usec = next->tv_usec - priv->tv_usec;
	if (sec) {
		consume = sec * 1000000 + usec;
	} else {						
		consume =usec;	
	}							
	
	printf("(%x)Consume time = %lld\n", 
		(int)pthread_self(), consume);
}

void do_prime(long long value)
{
	long long i;
	int flag = 0;

	for (i = 2; i < value; i++) {
		if ((value % i) == 0) {
			flag = 1;
			break;
		}
	}

	if (flag == 0) {
		printf("%lld  is a prime!\n", 
			 value);
	} else {
		printf("%lldis not a prime!\n", value);
	}
}

void * thread_handler(void * arg)
{
	printf("My tid is %x\n", (int)pthread_self());
	int ret, policy;
	struct sched_param param;

	ret = pthread_getschedparam(pthread_self(), 
		&policy, &param);
	if (ret) {
		printf("get schedparam:%s\n",
			strerror(ret));
		return NULL;	
	}	
	
	if (policy == SCHED_OTHER)
		printf("policy:SCHED_OTHER");
	else if (policy == SCHED_FIFO)	
		printf("policy:SCHED_FIFO");
	else if (policy == SCHED_RR)	
		printf("policy:SCHED_RR");
	printf("\n");	

	struct timeval priv, next;
	gettimeofday(&priv, NULL);
	do_prime(300000007);
	gettimeofday(&next, NULL);

	testTime(&priv, &next);
	return NULL;
}

int main(void)
{
	pthread_t tid;
	int ret;
	pthread_attr_t attr;
	int policy, inher;
	struct sched_param param;

	policy = SCHED_FIFO;
	param.sched_priority = 99;


	pthread_attr_init(&attr);
	
	pthread_attr_getinheritsched(&attr, &inher);
	if (inher == PTHREAD_INHERIT_SCHED)
		printf("Can't change sched policy!\n");
	else if (inher == PTHREAD_EXPLICIT_SCHED)	
		printf("Can change sched policy!\n");
#if 1
	pthread_attr_setinheritsched(&attr, 
		PTHREAD_EXPLICIT_SCHED);

	ret = pthread_attr_setschedpolicy(&attr, policy);
	if (ret) {
		printf("set policy:%s\n",
			strerror(ret));
		exit(1);
	}

	ret = pthread_attr_setschedparam(&attr, &param);
	if (ret) {
		printf("set policy:%s\n",
			strerror(ret));
		exit(1);
	}
#endif
	ret = pthread_create(&tid, &attr,
		thread_handler, NULL);
	if (ret) {
		printf("pthread_create:%s\n",
			strerror(ret));
		exit(1);	
	}
	struct timeval priv, next;
	gettimeofday(&priv, NULL);
	do_prime(300000007);
	gettimeofday(&next, NULL);

	testTime(&priv, &next);
	pthread_exit(NULL);
}
