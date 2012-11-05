#ifndef __HEAD_H
#define __HEAD_H


#define PIPESIZE 65536

typedef enum {
	FULL,
	NORMAL,
	EMPTY
} STATUS;
typedef enum {
	READ,
	WRITE
} RDWRFLAG;

typedef struct {
	char buf[PIPESIZE];
	int head;
	int tail;
	STATUS state;
	pid_t rpid;
	pid_t wpid;
} PIPE;

int createPipe(PIPE **pipe);
void setRDWRflag(PIPE * pipe, RDWRFLAG flag);

int readPipe(PIPE * pipe, char * buf, int size);
int writePipe(PIPE *pipe, const char * buf, int size);

int closePipe(PIPE *pipe);

#endif
