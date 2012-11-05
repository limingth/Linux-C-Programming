#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


char * readConsel(void)
{
	char *ptr = NULL;
	int ret;
	size_t n;

	ret = getline(&ptr, &n, stdin);
	if (ret == -1) {
		ptr = NULL;
	}
	
	return ptr;

}

int caculateCmdNum(char *buf)
{
	int i = 0, cnt = 0;

	while (1) {
		if (buf[i] == 0)
			break;
		if (buf[i] == ' ') {
			i++;	
			continue;
		} else {
			if ((i != 0) && 
				(buf[i-1] == ' '))
				cnt += 1;
			else if (i == 0)
				cnt += 1;
		}

		i++;
	}
	return cnt;
}

int ifPiped(char **argv)
{
	int fstart = 0;
	int i = 0;
	int fd[2], ret;
	pid_t pid;

	while (1) {
		if (argv[i] == NULL)
			break;
		if (strcmp(argv[i], "|") == 0 && 
			(i > 0)) {
			argv[i] = NULL;
			fstart = i+1;
			break;
		}
		i++;
	}
	if (fstart <= 1) {
		return -1;
	}
	pid = fork();
	if (pid == 0) {
		ret = pipe(fd);
		if (ret == -1) {
			perror("pipe");
			return -1;
		}
		pid_t Pid;
		Pid = fork();
		if (Pid == 0) {
			close(fd[0]);
			dup2(fd[1], 1);
			execvp(argv[0], argv);		
		}
		if (Pid > 0) {
			close(fd[1]);
			waitpid(Pid, NULL, 0);
			dup2(fd[0], 0);
			execvp(argv[fstart], 
				&argv[fstart]);
		}
	}
	
	waitpid(pid, NULL, 0);

	return 0;
}

int ifChdir(char **argv)
{
	if (strcmp(argv[0], "cd") == 0) {
		chdir(argv[1]);
		return 1;
	}	
		

	else
		return 0;
}

void parseCommand(char *buf)
{
	int ret, cnt, i = 0;
	char *ptr = buf;
	char *retptr = NULL;
	char *delimit = " ";

	cnt = caculateCmdNum(buf);
	if (cnt == 0)
		return;
	
	char *argv[cnt+1];


	while (1) {
		retptr = strtok(ptr, delimit);
		if (retptr)
			argv[i++] = retptr;
		else
			break;
		ptr = NULL;
	}
	argv[cnt] = NULL;
	if (ifChdir(argv))
		return;
	if (!ifPiped(argv))
		return;

	pid_t pid = fork();
	if (pid > 0)
		return;
	ret = execvp(argv[0], argv);
	if (ret == -1) {
		perror("execvp");
		exit(1);
	}
	waitpid(pid, NULL, 0);
}


int main(void)
{
	char *buf = NULL;

	while (1) {
		printf("%%%:");
		fflush(stdout);
		buf = readConsel();
		if (buf) {	
			buf[strlen(buf)-1] = '\0';
			parseCommand(buf);
			free(buf);
		}
	}

}
