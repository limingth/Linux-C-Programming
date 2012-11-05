#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>

#define CHILDNUM 5
//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock;

void * thread_func(void * arg)
{
	FILE * fp = (FILE *)arg;
	int n;
	char buf[32];
	int semid;

	printf("Hello this is %d\n", pthread_self());
	pthread_mutex_lock(&lock);
	printf("%d got the mutex!\n", pthread_self());
	fseek(fp, 0, SEEK_SET);
	fgets(buf, 32, fp);
	if (buf[strlen(buf)-1] == '\n')
		buf[strlen(buf)-1] = '\0';

	n = atoi(buf);
	fseek(fp, 0, SEEK_SET);
	sleep(3);
	fprintf(fp, "%d", n+1);
	fflush(fp);
	pthread_mutex_unlock(&lock);
	return NULL;
}


int main(void)
{
	pthread_t tid[CHILDNUM];
	int i, ret;
	
	FILE * fp;

	fp = fopen("tmp", "r+");
	if (fp == NULL) {
		perror("fopen");
		exit(1);
	}

	pthread_mutex_init(&lock, NULL);
	for (i = 0; i < CHILDNUM; i++) {
		ret = pthread_create(tid+i,
			NULL, thread_func, 
			(void *)fp);
		if (ret) {
			fprintf(stderr, "%s\n", 
				strerror(ret));
			exit(1);	
		}	
	}

	for (i = 0; i < CHILDNUM; i++) {
		pthread_join(tid[i], NULL);
	}

	pthread_mutex_destroy(&lock);
	fclose(fp);

	exit(0);

}
