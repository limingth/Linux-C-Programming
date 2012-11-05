#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void * thread_handler(void * arg)
{
	int oldstate, oldtype;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	if (oldstate == PTHREAD_CANCEL_ENABLE)
		printf("thread default enable canceled!\n");
		
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, 
		&oldtype);
	if (oldtype == PTHREAD_CANCEL_DEFERRED)
		printf("thread cancel defferred!\n");
	long long i = 0;
	int k;
	for (k = 0; k < 10; k++) {
		while (1) {
			i++;
			if (i == 999999999)
				break;
			//pthread_testcancel();	
		}
		i = 0;
		if (k == 2)
			sleep(1);
	}
	printf("thread over!\n");
	return NULL;
}

int main(void)
{
	pthread_t tid;
	int ret;
	char c;

	ret = pthread_create(&tid, NULL, thread_handler, NULL);
	if (ret) {
		printf("pthread_create:%s\n", strerror(ret));
		exit(1);
	}

	while (1) {
		printf("Input d cancel the thread!\n");
		scanf("%c", &c);
		if (c == 'd') {
			ret = pthread_cancel(tid);
			if (ret) {
				printf("pthread_cancel:%s\n",
					strerror(ret));
				exit(1);	
			}
			break;
		}
	}

	pthread_exit(NULL);
}
