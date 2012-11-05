#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int delete_shm(int shmid)
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
	}

	return 0;
}


int main(void)
{
	int shmid;
	pid_t pid;
	char *ptr = NULL;

	shmid = shmget(IPC_PRIVATE, 4096, 
		IPC_CREAT | 0600);
	if (shmid == -1) {
		perror("shmget");
		exit(1);
	}

	ptr = (char *)shmat(shmid, NULL, 0);
	if (ptr == ((void *)(-1))) {
		perror("shmat");
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		shmdt(ptr);
		perror("fork");
		exit(1);
	}

	if (pid == 0) {
		strcpy(ptr, "Hello world!\n");
		shmdt(ptr);
		delete_shm(shmid);
		exit(0);
	}

	if (pid > 0) {
		wait(NULL);
		printf("%s", ptr);
		shmdt(ptr);
		delete_shm(shmid);
		exit(0);
	}
}
