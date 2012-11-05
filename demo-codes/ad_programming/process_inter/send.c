#include "comm.h"

int writeFileToSharedMemory(const char * path, void ** addr)
{
	int fd, ret, shmid, semid, fileLen, offset = 1;
	char buf[100];
	struct stat fileStat;
	char * shmaddr = NULL;

	ret = stat(path, &fileStat);
	if (ret == -1) {
		perror("stat");
		return -1;
	}

	if (!S_ISREG(fileStat.st_mode)) {
		printf("File type wrong!\n");
		return -1;
	}
	
	fileLen = fileStat.st_size;

	shmid = shm_init(fileLen + 1);
	if (shmid == -1)
		return -1;
	shmaddr = (char *)get_shm_addr(shmid);
	if (shmaddr == NULL) {
		shm_delete(shmid);
		return -1;
	}

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("open");
		shm_exit(shmaddr);
		shm_delete(shmid);
		return -1;
	}

	semid = sem_init();

	p(semid);
	while (1) {
		ret = read(fd, buf, 100);
		if (ret == 0)
			break;
		if (ret > 0) {
			write_shm(shmaddr, buf, offset, ret);
			offset += ret;
		}	
	}
	v(semid);

	*addr = shmaddr;
	return shmid;
}

int sendMessageToMessageQueue(int shmid, void * shmaddr)
{
	int ret, msgid, i, semid, cnt = 0;
	msg_t smsg, rmsg;
	pid_t rpid[255];
	char * ptr = NULL;

	msgid = msg_init();
	if (msgid == -1) {
		shm_exit(shmaddr);
		shm_delete(shmid);
		return -1;
	}	
	while (1) {
		ret = recvPacket(msgid, &rmsg, RPID,
			sizeof(rmsg));
		if (ret == -2) 
			return -1;
		if (ret == -1) {
			if (cnt == 0) {
				printf("There are no processes "
					"nees data!\n");
				return 0;	
			}
			break;
		}	
		rpid[cnt] = rmsg.data.pid;
		smsg.mtype = SPID;
		smsg.data.pid = getpid();
		sendPacket(msgid, &smsg, sizeof(smsg) - 
			sizeof(long));
		smsg.mtype = SHMID;
		smsg.data.shmid = shmid;
		sendPacket(msgid, &smsg, sizeof(smsg) - 
			sizeof(long));
		cnt++;
		if (cnt == 255)
			break;
	}
	semid = sem_init();
	p(semid);
	ptr = (char *)shmaddr;
	*ptr = cnt;
	v(semid);

	shm_exit(shmaddr);

	for (i = 0; i < cnt; i++) {
		kill(rpid[i], SIGUSR1);
	}

	return 0;
}

int main(void)
{
	char buf[100];
	int ret, shmid;
	void * shmaddr;

	while (1) {
		printf("Waitting your file:");
		fflush(stdout);

		ret = read(0, buf, 100);
		if (ret == -1) {
			perror("read");
			exit(1);
		}	
		
		buf[ret-1] = 0;

		shmid = writeFileToSharedMemory(buf, &shmaddr);
		if (shmid == -1)
			exit(1);
		ret = sendMessageToMessageQueue(shmid, shmaddr);
		if (ret == -1)
			exit(1);
	}
}
