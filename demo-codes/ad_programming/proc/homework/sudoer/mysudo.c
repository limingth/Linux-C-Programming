#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int getUid(char *buf)
{
	struct passwd *res = getpwnam(buf);

	return res->pw_uid;
}

int parse(char *tok, char *buf)
{
	int i = 0;
	if (strstr(buf, tok)) {
		while (buf[i++] != ':');
		buf[i-1] = '\0';
		return getUid(buf);
	} else
		return -1;
}

int readFile(char *cmd)
{
	FILE *fp = fopen("sudo", "r");
	if (fp == NULL) {
		perror("fopen");
		return -1;
	}
	char *buf = NULL;
	int ret, n, res;

	while (1) {
		ret = getline(&buf, &n, fp);
		if (ret > 0) {
			res = parse(cmd, buf);
			if (res == -1)
				continue;
			else
				return res;
		}
	}
	return -1;	
}

int done(char *cmd)
{
	uid_t uid = readFile(cmd);
	if (uid == -1) {
		printf("Command %s undefined!\n", cmd);
		return -1;
	}

	setuid(uid);
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 2) 
		return -1;
	int ret;

	ret = done(argv[1]);
	if (ret == -1)
		return -1;
	execlp(argv[1], argv[1], NULL);	
}
