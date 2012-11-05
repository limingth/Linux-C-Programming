#include "thread_pool.h"

static Thread_Poll_t *g_poll;
static int g_thread_num;

void * thread_handler(void * arg)
{
	Thread_Poll_t * thread = (Thread_Poll_t *)arg;

	while (1) {
		pthread_mutex_lock(&(thread->mutex));
		thread->status = IDLE;
		pthread_cond_wait(&(thread->cond), 
			&(thread->mutex));
		if (thread->task == NULL)
			continue;
		if ((thread->cnt += 1) < 0)
			thread->cnt = 0;
		thread->status = BUSY;
		pthread_mutex_unlock(&(thread->mutex));
		(thread->task)(thread->arg);
	}

	return NULL;
}

static int create_threads(Thread_Poll_t * thread, int num)
{
	int i, ret;
	
	for (i = 0; i < num; i++) {
		ret = pthread_create(&(thread[i].tid), NULL,
			thread_handler, (void *)(&thread[i]));
		if (ret) {
			fprintf(stderr, "pthread_create:%s\n",
				strerror(ret));
			return -1;	
		}	
	}

	return 0;
}

void wait_thread_ready(Thread_Poll_t * thread, int num)
{
	int i;

	for (i = 0; i < num; i++) {
		while (1) {
			if (thread[i].status == WAITTING) {
				sched_yield();
				continue;
			} else if (thread[i].status == IDLE)
				break;
		}
	}
}

int threadPoll_create_and_init(int num)
{
	if (num <= 0) 
		return -1;
	
	int i, ret;
	Thread_Poll_t * thread;

	thread = (Thread_Poll_t *)malloc(
		num * sizeof(Thread_Poll_t));
	if (thread == NULL) {
		perror("malloc");
		return -1;
	}	

	g_poll = thread;
	g_thread_num = num;

	for (i = 0; i < num; i++) {
		pthread_cond_init(&(thread[i].cond), NULL);
		pthread_mutex_init(&(thread[i].mutex), NULL);
		thread[i].status = WAITTING;
		thread[i].task = NULL;
		thread[i].arg = NULL;
		thread[i].cnt = 0;
	}

	ret = create_threads(thread, num);
	if (ret == -1)
		return -1;
	wait_thread_ready(thread, num);

	return 0;
}


int threadPoll_assign_work(task_t task, void * arg)
{
	int i, num, index, record = -1;
	Thread_Poll_t * thread;

	thread = g_poll;
	num = g_thread_num;

	if ((thread == NULL) || (num == 0))
		return -1;
	
	for (i = 0; i < num; i++) {
		pthread_mutex_lock(&(thread[i].mutex));
		if (thread[i].status == IDLE) {
			if (record == -1) {
				record = thread[i].cnt;
				index = i;
			} else {
				if (thread[i].cnt < record) {
					record = thread[i].cnt;
					index = i;
				}	
			}	
		}
		pthread_mutex_unlock(&(thread[i].mutex));

	}

	if (record != -1) {
		pthread_mutex_lock(&(thread[index].mutex));
		thread[index].status = ASSIGNED;
		thread[index].task = task;
		thread[index].arg = arg;
		pthread_cond_signal(&(thread[index].cond));
		pthread_mutex_unlock(&(thread[index].mutex));
	} else {
		printf("Error:All threads are busy!\n");
		return -1;
	}

	return 0;
}
