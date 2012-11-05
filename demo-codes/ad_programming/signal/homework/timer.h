#ifndef __TIMER__H
#define __TIMER__H

typedef void(*jobFunc)(int);

enum {
	WAITTING,
	RUNNING,
	COMPLETED
};

typedef struct {
	int nsec; //到期时间
	jobFunc job;//到期执行任务
	int taskId;
	int flag;
} JOB_T;

int add_job(int taskid, jobFunc job, int expire);
int del_job(int taksID);


#endif
