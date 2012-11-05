#include "comm.h"

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

void destroy_zombie(void)
{
	struct sigaction act;
	act.sa_handler = SIG_IGN;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDWAIT;

	sigaction(SIGCHLD, &act, NULL);
}

int getReqFromClient(int msgid, REQ_T *data)
{
	int msgsz = sizeof(REQ_T);
	int ret;

	ret = msgrcv(msgid, data, msgsz, REQTYPE, 0);
	if (ret == -1) {
		perror("msgrcv");
		return ret;
	}

	return 0;
}

int processData(int msgid, REQ_T *req)
{
	int repType, fd, ret, len, r;
	char *path;
	REP_T rep;

	repType = req->data.type;
	path = req->data.filePath;

	fd = open(path, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return -1;
	}

	rep.mtype = repType;
	len = sizeof(rep) - sizeof(long);
	while (1) {
		ret = read(fd, rep.data.packetContent, 
			PACKETSIZE);
		if (ret == -1) {
			perror("read");
			return -1;
		}	
		if (ret >= 0) {
			rep.data.packetSize = ret;
			r = msgsnd(msgid, &rep, len, 0);
			if (r == -1) {
				perror("msgsnd");
				return -1;
			}
			if (ret == 0)
				break;
		}
	}
	
	return 0;
}

int main(void)
{
	int msgid, ret;
	REQ_T req;
	pid_t pid;

	msgid = msg_init();
	if (msgid == -1) {
		exit(1);
	}

	destroy_zombie();

	while (1) {
		ret  = getReqFromClient(msgid, &req);
		if (ret == -1) {
			continue;
		}
		pid = fork();
		if (pid == -1) {
			perror("fork");
			exit(1);
		}
		if (pid == 0) {
			ret = processData(msgid, &req);
			exit(0);
		}
	
	}
}
