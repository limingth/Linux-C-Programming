#ifndef __COMM__H
#define __COMM__H
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define PATHNAME "/etc/passwd"
#define KEY_ID 25
#define REQTYPE 2
#define PACKETSIZE 512

typedef struct {
	int type;
	char filePath[256];
} REQ_DATA_T;

typedef struct {
	long mtype;
	REQ_DATA_T data;
} REQ_T;

typedef struct {
	int packetSize;
	char packetContent[PACKETSIZE];
} REP_DATA_T;

typedef struct {
	long mtype;
	REP_DATA_T data;
} REP_T;








#endif
