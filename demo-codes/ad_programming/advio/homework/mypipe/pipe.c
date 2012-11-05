#include "head.h"

int createPipe(PIPE ** pipe)
{
	PIPE * sbuf = (PIPE *)mmap(NULL, sizeof(PIPE), 
		PROT_READ | PROT_WRITE, MAP_SHARED |
		MAP_ANONYMOUS, -1, 0);
	if (sbuf == MAP_FAILED) {
		perror("mmap");
		return -1;
	}	

	sbuf->head = 0;
	sbuf->tail = 0;
	sbuf->state = EMPTY;
	sbuf->rpid = -1;
	sbuf->wpid = -1;

	*pipe = sbuf;
	return 0;
}

void setRDWRflag(PIPE * pipe, RDWRFLAG flag)
{
	if (flag == READ) 
		pipe->rpid = getpid();
	else if (flag == WRITE)
		pipe->wpid = getpid();
	return;
}

static char readOneByte(PIPE *pipe)
{
	char c;
	if (pipe->state == EMPTY)
		return -1;

	c = (pipe->buf)[(pipe->tail)++];
	if (pipe->tail >= PIPESIZE)
		pipe->tail = 0;
	if (pipe->head == pipe->tail)
		pipe->state = EMPTY;
	else
		pipe->state = NORMAL;

	return c;
}

int readPipe(PIPE * pipe, char * buf, int size)
{
	int i;
	if ((buf == NULL) || (size <= 0)) {
		printf("invalied argument for read!\n");
		return -1;
	}

	if (pipe->rpid != getpid()) {
		printf("read permition denied!\n");
		return -1;
	}
	
	for (i = 0; i < size; i++) {
		if ((buf[i] = readOneByte(pipe)) == -1)
			break;
	}
	return i;
}

char writeOneByte(PIPE * pipe, char c)
{
	if (pipe->state == FULL)
		return -1;
	(pipe->buf)[(pipe->head)++] = c;
	if (pipe->head >= PIPESIZE)
		pipe->head = 0;
	if (pipe->head == pipe->tail)
		pipe->state = FULL;
	else
		pipe->state = NORMAL;
	return c;	
}

int writePipe(PIPE * pipe, const char * buf, int size)
{
	int i;
	if ((buf == NULL) || (size <= 0)) { 
		printf("invalied argument for write!\n");
		return -1;
	}

	if (pipe->wpid != getpid()) {
		printf("write permition denied!\n");
		return -1;
	}

	for (i = 0; i < size; i++) {
		if (writeOneByte(pipe, buf[i]) == -1)
			break;
	}	

	return i;
}

int closePipe(PIPE * pipe)
{
	if (pipe == NULL)
		return -1;
	munmap(pipe, sizeof(PIPE));
	return 0;
}
