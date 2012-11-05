#include "comm.h"
#include <string.h>


int msg_init(void)
{
	int ret = 0;
	key_t key = ftok(PATHNAME, KEY_ID);
	if (key == -1) {
		perror("ftok");
		ret = key;
	}

	int msgid = msgget(key, IPC_CREAT | 0600);
	if (msgid == -1) {
		perror("msgget");
	}

	ret = msgid;
	return ret;	
}

int sendReqToServer(int msgid, const char *path)
{
	REQ_T req;
	int ret, msgsize;
	bzero(&req, sizeof(req));

	req.mtype = REQTYPE;
	msgsize = sizeof(REQ_T) -sizeof(long);

	strncpy(req.data.filePath, path, 
		strlen(path));
	req.data.type = getpid();	

	ret = msgsnd(msgid, &req, msgsize, 0);
	if (ret == -1) {
		perror("msgsnd");
		return -1;
	}

	return 0;
}

int processData(int msgid, const char *path)
{
	int fd, ret, len, mtype;
	REP_T rep;

	fd = creat(path, 0644);
	if (fd == -1) {
		perror("creat");
		return -1;
	}

	len = sizeof(rep);
	mtype = getpid();

	while (1) {
		ret = msgrcv(msgid, &rep, len, 
			mtype, 0);
		if (ret == -1) {
			perror("msgrcv");
			return -1;
		}
		if (rep.data.packetSize == 0)
			break;
		write(fd, rep.data.packetContent,
			rep.data.packetSize);
		usleep(500000);
		printf("..");
		fflush(stdout);
	}

	close(fd);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		return -1;
	}
	
	int msgid, ret;

	msgid = msg_init();
	if (msgid == -1) {
		exit(1);
	}

	ret = sendReqToServer(msgid, argv[1]);
	if (ret == -1) {
		exit(1);
	}

	ret = processData(msgid, argv[2]);
	if (ret == -1) {
		exit(1);
	}

	exit(0);

}
