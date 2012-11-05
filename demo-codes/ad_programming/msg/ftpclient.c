#include "comm.h"

int msgid;

int main(int argc, const char *argv[])
{
	key_t msgkey = ftok(FILEPATH, ID);
	msgid = msgget(msgkey, MSGFLG);
	PMSG msgbuf = (PMSG)malloc(sizeof(long)+128);
	PMSG pmsg_filetmp = (PMSG)calloc(sizeof(long)+sizeof(MSG_FILE), 1);
	
	if(msgbuf == NULL)
	{
		perror("msgbuf::malloc");
		exit(-1);
	}
	size_t ret;
	int fileid;

	msgbuf->mtype = REQUEST;
	sprintf(msgbuf->mtext, "%s", argv[1]);
	msgsnd(msgid, msgbuf, sizeof(long)+128, 0);
	ret = msgrcv(msgid, msgbuf, sizeof(long)+128, FILEID, 0);
	if(ret == -1)
	{
		perror("msgrcv");
		exit(-1);
	}
	fileid = *((int *)msgbuf->mtext);

	printf("fileid:%d\n",fileid);
	if(pmsg_filetmp == NULL)
	{
		perror("msg_file::malloc");
		exit(-1);
	}
	printf("pmsg_filetmp::malloc correct");
	MSG_FILE msg_file;
	int fd = open(argv[2], O_CREAT|O_WRONLY, 0600);
	if(fd == -1)
	{
		perror("open");
		exit(-1);
	}
	printf("open correct\n");
	while(1)
	{
		ret = msgrcv(msgid, pmsg_filetmp, sizeof(long)+sizeof(MSG_FILE), fileid, 0);
		if(ret == -1)
		{
			perror("while::msgrcv");
			exit(-1);
		}
		memcpy(&msg_file, pmsg_filetmp->mtext, sizeof(MSG_FILE));
		if(msg_file.flag == 0)
		{
			msgbuf->mtype = REPLY;
			msgsnd(msgid, msgbuf, sizeof(long)+128, 0);
			break;
		}
		write(fd, msg_file.filedata, msg_file.flag);

	}
	close(fd);

	return 0;
}
