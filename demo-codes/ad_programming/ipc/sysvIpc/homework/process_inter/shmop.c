#include "comm.h"

static void *shmaddr = NULL;

int shm_init(int size)
{
	key_t key;
	int shmid;

	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		return -1;
	}
	
	shmid = shmget(key, size, 
		IPC_CREAT | IPC_EXCL | 0600);
	if (shmid == -1) {
		if (errno == EEXIST) {
			
		}
	}	

	shmid = shmget(key, size, IPC_CREAT | 0600);
	if (shmid == -1) {
		perror("shmget");
		return -1;
	}

	shmaddr = shmat(shmid, NULL, 0);
	if (((void *)(-1)) == shmaddr) {
		perror("shmat");
		return -1;
	}

	return shmid;
}

void write_shm(const void * buf, int offset, int len)
{
	memcpy(shmaddr+offset, buf, len);
}

void read_shm(char * buf, int offset, int len)
{
	memcpy(buf, shmaddr+offset, len);
}

int shm_delete(int shmid)
{
	struct shmid_ds buf;
	int ret;

	ret = shmctl(shmid, IPC_STAT, &buf);
	if (ret == -1) {
		perror("shmctl");
		return -1;
	}
	if (buf.shm_nattch == 0) {
		ret = shmctl(shmid, IPC_RMID, NULL);
		if (ret == -1) {
			perror("shmctl");
			return -1;
		}
		return 0;
	}

	return 1;
}

void shm_exit(void)
{
	shmdt(shmaddr);
}

