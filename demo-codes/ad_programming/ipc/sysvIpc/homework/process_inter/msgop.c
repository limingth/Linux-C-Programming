#include "comm.h"

int msg_init(void)
{
	key_t key;
	int msgid;

	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		return -1;
	}

	msgid = msgget(key, IPC_CREAT | 0600);
	if (msgid == -1) {
		perror("msgget");
		return -1;
	}

	return msgid;
} 

int sendPacket(int msgid, const void * buf, int len)
{
	int ret;

	ret = msgsnd(msgid, buf, len, 0);
	if (ret == -1) {
		perror("msgsnd");
		return -1;
	}
	return 0;
}

int recvPacket(int msgid, void * buf, int type, int len)
{
	int ret;

	ret = msgrcv(msgid, buf, len, type, IPC_NOWAIT);
	if (ret == -1) {
		if (errno == ENOMSG)
			return -1;
		else {
			perror("msgrcv");
			return -2;
		}	
	}

	return 0;
}
