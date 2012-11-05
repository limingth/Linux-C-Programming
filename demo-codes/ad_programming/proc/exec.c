#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

//	execl("/bin/ls", 
//		"ls", "-a", "-l", "/", NULL);
//	execlp("ls", 
//		"ls", "-a", "-l", "/", NULL);

	char *argv[] = {
		"ls",
		"-a",
		"-l",
		NULL
	};

//	execv("/bin/ls", argv);
	execvp(argv[0], argv);
}
