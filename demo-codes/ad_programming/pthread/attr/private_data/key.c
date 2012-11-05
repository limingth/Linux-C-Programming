#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

pthread_key_t key;

static void free_data(void * arg)
{
	printf("Destructot!");
	free(arg);
}

void str_display(void)
{

	char * str = (char *)pthread_getspecific(key);
	if (str == NULL) {
		printf("getspecific wrong!\n");
		return;
	}

	printf("Thread:%x: %s", (int)pthread_self(), str);

	return;
}

void * thread_handler(void * arg)
{
	int ret;
	int i = (int)arg;
	char * str = (char *)malloc(100);
	if (!str) {
		exit(1);
	}

	sprintf(str, "This is %d\n", i);
	ret = pthread_setspecific(key, (void *)str);
	if (ret) {
		fprintf(stderr, "setspecific:%s\n",
			strerror(ret));
		return NULL;	
	}

	str_display();

	return NULL;
}

int main(void)
{
	int ret, i;
	pthread_t tid[3];
	pthread_attr_t attr;

	ret = pthread_key_create(&key, free_data);
	if (ret) {
		printf("key_create:%s\n", strerror(ret));
		exit(1);
	}
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, 
		PTHREAD_CREATE_DETACHED);

	for (i = 0; i < 3; i++) {
		ret = pthread_create(tid+i, &attr, thread_handler,
			(void *)i);
		if (ret) {
			fprintf(stderr, "thread_create:%s\n",
				strerror(ret));
			exit(1);	
		}	
	}

	pthread_attr_destroy(&attr);

	pthread_exit(NULL);
}
