#include <stdio.h>


pid_t fork(void)
{
	...
	..
	pid = create a child
	if (father)
		return pid;
	if (child)
		return 0;
}

pid_t pid;

pid = fork();















int x;

int main(void)
{

	printf("x`s addr= 0x%x\n", &x);

	while (1) {
		sleep(1);
	}
}

