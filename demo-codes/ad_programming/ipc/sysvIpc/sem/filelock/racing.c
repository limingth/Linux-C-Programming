#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#define KEYPATH "/etc/passwd"
#define KEYID 20

int creat_sem(int num)
{
	int semid, ret;
	key_t key;
	
	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		return -1;
	}

	semid = semget(key, num, 
		IPC_CREAT | 0600);
	if (semid == -1) {
		perror("semget");
		return -1;
	}

	return semid;
}

int init_semphore(int semid, int numth, int val)
{
	int ret;

	ret = semctl(semid, numth, SETVAL, val);
	if (ret == -1) {
		perror("semctl");
		return -1;
	}

	return 0;
}

int p(int semid, int numth)
{
	int ret;
	struct sembuf op;

	op.sem_num = numth;
	op.sem_op = -1;
	op.sem_flg = 0;

	while (1) {
		ret = semop(semid, &op, 1);
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			else {
				perror("semop");
				return -1;
			}	
		}
		if (ret == 0)
			break;
	}

	return 0;
}


void v(int semid, int numth)
{
	int ret;
	struct sembuf op;

	op.sem_num = numth;
	op.sem_op = 1;
	op.sem_flg = 0;

	semop(semid, &op, 1);

	return;
}


int file_op(void)
{
	FILE *fp;
	int i = 0;

	fp = fopen("tmp", "a");
	if (!fp) {
		perror("fopen");
		return -1;
	}

	while (1) {
		fprintf(fp, "This is %d, the %d line\n",
			getpid(), i);
		fflush(fp);
		usleep(300000);
		i++;
		if (i == 30)
			break;		
	}

	fclose(fp);
	return 0;
}

int main(void)
{
	int ret, semid;
	
	semid = creat_sem(1);
	if (semid == -1) {
		exit(1);
	}
	ret = init_semphore(semid, 0, 1);
	if (ret == -1) {
		exit(1);
	}
	p(semid, 0);
	printf("pid=%d is operating!\n", getpid());
	file_op();
	v(semid, 0);
	return 0;
}
