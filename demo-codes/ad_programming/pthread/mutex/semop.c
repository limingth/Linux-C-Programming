#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <errno.h>

#define KEYPATH "/etc/passwd"
#define KEYID 22

static int creat_sem(int num, int * status)
{
	int semid, ret;
	key_t key;

	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		return -1;
	}

	semid = semget(key, num, 
		IPC_CREAT | IPC_EXCL | 0600);
	if (semid == -1) {
		if (errno == EEXIST) {
			*status = 3;
			return semget(key, num, 0);
		}	
		perror("semget");
		return -1;
	}	

	return semid;
}

int sem_init()
{
	int ret, semid;
	int status = 0;

	semid = creat_sem(1, &status);
	if (semid == -1)
		return -1;
	if (status == 3)
		return semid;
	ret = semctl(semid, 0, SETVAL, 1);
	if (ret == -1) {
		perror("semctl");
		return -1;
	}	
	return semid;
}

int p(int semid)
{
	int ret;
	struct sembuf op;

	op.sem_num = 0;
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

int v(int semid)
{
	int ret;
	struct sembuf op;

	op.sem_num = 0;
	op.sem_op = 1;
	op.sem_flg = 0;

	semop(semid, &op, 1);

	return;
}
