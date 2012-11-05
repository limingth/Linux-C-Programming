#include "comm.h"

int hash[512];
int msgid;
int check_fileid()
{
	int i;
	PMSG pmsg_fileid = (PMSG)malloc(sizeof(long)+sizeof(int));

FULL:
	for(i = 5; i < 512; i++)
	{
		if(hash[i] == 0)
		{
			hash[i] = 1;
			break;
		}
	}
	if(i == 512)
	{
		sleep(1);
		goto FULL;
	}

	pmsg_fileid->mtype = FILEID;
	memcpy(pmsg_fileid->mtext, &i, 4);
	msgsnd(msgid, pmsg_fileid, sizeof(long)+128, 0);
	free(pmsg_fileid);
	return i;
}

int sendfile(char *filename)
{
	int i;
	i = check_fileid();
	
	pid_t pid;
	pid = fork();
	if(pid == 0)
	{
		int fd = open(filename, O_RDONLY);
		if(fd == -1)
		{
			perror("open");
			exit(-1);
		}
		int rdret;
		MSG_FILE msg_file;
		PMSG pmsg_file = (PMSG)malloc(sizeof(long)+sizeof(MSG_FILE));

		fcntl(fd, F_SETFL, O_NONBLOCK);
		printf("fileid:%d,file:%s\n", i, filename);
		
		while(1)
		{
			rdret = read(fd, &(msg_file.filedata), 4096);
			msg_file.flag = rdret;
			if(rdret <= 0)
			{
				msg_file.flag = 0;
				//发送数据包。
				memcpy(pmsg_file->mtext, &msg_file, sizeof(MSG_FILE));
				pmsg_file->mtype = i;
				msgsnd(msgid, pmsg_file, sizeof(long)+sizeof(MSG_FILE), 0);
				break;
			}
			memcpy(pmsg_file->mtext, &msg_file, sizeof(MSG_FILE));
			pmsg_file->mtype = i;
			msgsnd(msgid, pmsg_file, sizeof(long)+sizeof(MSG_FILE), 0);
		}
		exit(1);
	}
	return 0;
}

int destory_child()
{
	struct sigaction sig;
	sig.sa_handler = SIG_IGN;
	sigemptyset(&(sig.sa_mask));
	sig.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &sig, NULL);
}

int main(int argc, const char *argv[])
{
	key_t msgkey = ftok(FILEPATH, ID);
	PMSG msgbuf = (PMSG)malloc(sizeof(long)+128);
	size_t ret;
	msgid = msgget(msgkey, MSGFLG);
	destory_child();

	while(1)
	{
		ret = msgrcv(msgid, msgbuf, sizeof(long)+128, -2, 0);
		if(ret == -1)
		{
			perror("msgrcv");
			exit(-1);
		}
		if(msgbuf->mtype == 2) //如果是回复，就还原哈希
		{
			int fileid = *((int *)msgbuf->mtext);
			hash[fileid] = 0;
			continue;
		}
		printf("file:%s\n", msgbuf->mtext);
		sendfile(msgbuf->mtext);

	}
	return 0;
}
