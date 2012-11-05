#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define PATH "./comm.h"
#define ID 512
typedef struct {
	long mtype;
	char mtext[1];
}MSG,*PMSG;

int main(int argc, const char *argv[])
{
	key_t key_ipc = ftok(PATH, ID);
	int id_msg = msgget(key_ipc, IPC_CREAT);
	PMSG msgbuf = (PMSG)malloc(sizeof(long)+100);
	while(1)
	{
		scanf("%s",msgbuf.mtext);
		msgbuf.mtype = 1;
		msgsnd(id_msg, &msgbuf, sizeof(long)+strlen(msgbuf.mtext+1), 0);
	}
	msgctl(id_msg, IPC_RMID, NULL);
	return 0;
}
