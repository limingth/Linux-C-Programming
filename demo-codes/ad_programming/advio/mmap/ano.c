#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
	int ret;
	struct stat buf;
	char * ptr = NULL;
	pid_t pid;

	ptr = (char *)mmap(NULL, 32, PROT_READ | 
		PROT_WRITE, MAP_SHARED |
			MAP_ANONYMOUS, -1, 0);
	if (((void *)(-1)) == ptr) {
		perror("mmap");
		exit(1);
	}	


	pid = fork();
	if (pid == -1) {
		perror("fork");
		munmap(ptr, 32);
		exit(1);
	}

	if (pid == 0) {
		strcpy(ptr, "Hello World!\n");
		munmap(ptr, 32);
		exit(0);
	}

	if (pid > 0) {
		wait(NULL);
		printf("%s", ptr);
		munmap(ptr, 32);
		exit(0);
	}

	exit(0);
}
