#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define PATH "./comm.h"
#define ID 501
typedef struct {
	long mtype;
	char mtext[1];
}MSG,*PMSG;

int main(int argc, const char *argv[])
{
	key_t key_ipc = ftok(PATH, ID);
	int id_msg = msgget(key_ipc, IPC_CREAT | 0600);
	PMSG msgbuf = (PMSG)malloc(sizeof(long)+100);
//	while(1)
//	{
		scanf("%s",msgbuf->mtext);
		msgbuf->mtype = 1;
		msgsnd(id_msg, msgbuf, sizeof(long)+100, 0);
//	}
	//msgctl(id_msg, IPC_RMID, NULL);
	return 0;
}
