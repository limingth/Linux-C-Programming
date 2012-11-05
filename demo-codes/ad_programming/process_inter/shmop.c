#include "comm.h"

int shm_init(int size)
{
	key_t key = IPC_PRIVATE;
	int shmid;

	shmid = shmget(key, size,
		IPC_CREAT | 0600);
	if (shmid == -1) {
		perror("shmget");
		return -1;
	}	

	return shmid;
}

void * get_shm_addr(int shmid)
{
	void *shmaddr = shmat(shmid, NULL, 0);
	if (((void *)(-1)) == shmaddr) {
		perror("shmat");
		return NULL;
	}

	return shmaddr;
		
}

int get_shm_size(int shmid)
{
	int ret;
	struct shmid_ds buf;

	ret = shmctl(shmid, IPC_STAT, &buf);
	if (ret == -1) {
		perror("shmctl");
		return -1;
	}
	
	return buf.shm_segsz;
}

void write_shm(void * shmaddr, const void * buf, int offset,
			int len)
{
	memcpy(shmaddr + offset, buf, len);
}			

void read_shm(void * shmaddr, char *buf, int offset, int len)
{
	memcpy(buf, shmaddr + offset, len);
}

void shm_exit(void * shmaddr)
{
	shmdt(shmaddr);
}

int shm_delete(int shmid)
{
	int ret;
	struct shmid_ds buf;

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

	return -1;
}
