#ifndef __COMMEN_VESTIGE__
#define __COMMEN_VESTIGE__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#define     FILEPATH "/etc/passwd"
#define     MSGFLG   IPC_CREAT|0600
#define     ID       30

typedef struct {
	long mtype;  //
	char mtext[1];
}MSG,*PMSG;

typedef struct {
	int flag;
	char filedata[4096];
}MSG_FILE,*PMSG_FILE;

enum{
	REQUEST = 1,
	REPLY,
	SENDFILE,
	FILEID
};

#endif
