#include "comm.h"

static int msgid;

int check_pid(pid_t pid)
{
	int ret;
	msg_t rmsg;

	ret = recvPacket(msgid, &rmsg, 
		SPID, sizeof(rmsg));
	if (ret != 0)
		return -1;
	if (rmsg.data.pid == pid)	
		return 0;
	else
		return -1;
}

int get_shmid(void)
{
	int ret;
	msg_t rmsg;

	ret = recvPacket(msgid, &rmsg, 
		SHMID, sizeof(rmsg));
	if (ret != 0)
		return -1;
	
	return rmsg.data.shmid;
}

void shm_operation(int shmid)
{
	char * shmaddr;
	int size, semid;
	int cnt;

	semid = sem_init();

	p(semid);

	shmaddr = (char *)get_shm_addr(shmid);
	if (shmaddr == NULL) {
		shm_delete(shmid);
		return;
	}
	size = get_shm_size(shmid);
	if (size == -1) {
		shm_exit(shmaddr);
		shm_delete(shmid);
		return;
	}

	cnt = *shmaddr;
	cnt -= 1;
	*shmaddr = cnt;

	printf("Get file:\n");
	write(1, shmaddr+1, size);
	printf("\n**file end**\n");

	v(semid);

	shm_exit(shmaddr);

	if (cnt == 0)
		shm_delete(shmid);

	return;	
}

void shm_notify(int s, siginfo_t * info, void * context)
{
	int shmid, num;
	pid_t pid;

	pid = info->si_pid;

	if (0 == check_pid(pid)) {
		shmid = get_shmid();
		if (shmid == -1)
			return;
		shm_operation(shmid);	
	} else
		return;
}

void signal_regist(void)
{
	struct sigaction act;
	act.sa_sigaction = shm_notify;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART | SA_SIGINFO;

	sigaction(SIGUSR1, &act, NULL);
}

int sendPidToMessageQueue(void)
{
	msg_t smsg;
	int ret;

	smsg.mtype = RPID;
	smsg.data.pid = getpid();
	ret = sendPacket(msgid, &smsg, sizeof(smsg) -
		sizeof(long));
	return ret;
}

int main(void)
{
	msgid = msg_init();
	if (msgid == -1) {
		exit(1);
	}

	int ret = sendPidToMessageQueue();
	if (ret == -1) 
		exit(1);
	signal_regist();

	while (1) {
		sleep(rand() % 5 + 1);
	}
}
