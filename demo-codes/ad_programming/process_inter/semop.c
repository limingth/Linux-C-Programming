#include "comm.h"

static int creat_sem(int num)
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

int sem_init()
{
	int ret, semid;

	semid = creat_sem(1);
	if (semid == -1)
		return -1;
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
