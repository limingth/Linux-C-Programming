#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

char **argvv;

int regist(void)
{
	int fd = creat("tmp", 0666);
	write(fd, argvv[1], strlen(argvv[1]));	
	
	printf("exit!\n");
	return 0;
}
void func(int a)
{

}

int main(int argc, char **argv)
{
	func(regist());
//	atexit(regist);
	if (argc != 2)
		return -1;

	argvv = argv;


	if (strcmp(argv[1], "done") == 0) {
		exit(0);
	} else if (strcmp(argv[1], "quit") == 0) {
		exit(1);
	} else {
		exit(2);
	}	
}
