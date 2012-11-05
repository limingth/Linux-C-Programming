#include "thread_pool.h"

#define THREADNUM 3

void task(void * arg)
{
	int t = *((int *)arg);

	printf("I will sleep %d seconds!\n", t);
	sleep(t);
	printf("tid=%u task over!\n", (unsigned)pthread_self());
	return;
}

int main(void)
{
	 int i, ret;
	 int a[THREADNUM+1] = {7, 6, 5, 6};

	 ret = threadPoll_create_and_init(THREADNUM);
	 if (ret == -1) {
	 	printf("Thread create fail!\n");
	 	exit(1);
	 }

	ret = threadPoll_assign_work(task, (void *)&a[0]);
	if (ret == -1)
		exit(1);
	sleep(1);
	ret = threadPoll_assign_work(task, (void *)&a[1]);
	if (ret == -1)
		exit(1);
	sleep(1);	
	ret = threadPoll_assign_work(task, (void *)&a[2]);
	if (ret == -1)
		exit(1);

	while (threadPoll_assign_work(task, (void *)&a[3])
		== -1) {
		usleep(500000);	
	}
	
	while (1)
		sleep(1);
	exit(0);
}
