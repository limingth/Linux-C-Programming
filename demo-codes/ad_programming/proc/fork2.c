#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int a[10000] = {9};

int main(void)
{

	pid_t pid;

	pid = fork();
	if (pid == 0) {
		a[0]++;
		printf("In child a=%d, addr=%p\n", 
			a[0], a);
		exit(0);
	}

	wait(NULL);
	printf("In father a= %d\n, addr = %p\n", 
		a[0], a);
	
	exit(0);
}
