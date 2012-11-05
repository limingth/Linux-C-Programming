#ifndef __COMM_H
#define __COMM_H

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#define KEYPATH "/etc/passwd"
#define KEYID 22

enum {
	RPID = 3,
	SPID,
	SHMID
};

typedef struct {
	long mtype;
	union {
		pid_t pid;
		int shmid;
	} data;
} msg_t;



#endif
