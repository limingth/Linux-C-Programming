#include "head.h"

int createPipe(PIPE ** pipe)
{
	PIPE * sbuf = (PIPE *)mmap(NULL, sizeof(PIPE), 
		PROT_READ | PROT_WRITE, MAP_SHARED |
		MAP_ANONYMOUS, -1, 0);

	sbuf->head = 0;
	sbuf->tail = 0;
	sbuf->state = EMPTY;
	sbuf->rpid = -1;
	sbuf->wpid = -1;

	*pipe = sbuf;
	return 0;
}
