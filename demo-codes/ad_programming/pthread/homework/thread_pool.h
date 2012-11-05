#ifndef __THREAD_POOL_H
#define __THREAD_POOL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sched.h>
#include <errno.h>
#include <pthread.h>

typedef enum {
	WAITTING,
	IDLE,
	ASSIGNED,
	BUSY
} Thread_Status;

typedef void (*task_t)(void * arg);

typedef struct {
	pthread_t tid;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	Thread_Status status;
	task_t task;
	void * arg;
	int cnt;

} Thread_Poll_t;

int threadPoll_create_and_init(int num);
int threadPoll_assign_work(task_t task, void * arg);

#endif
