#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYPATH "/etc/passwd"
#define KEYID 123

typedef struct {
	//char *name;
	char name[32];
	float avg;
} score_t;

struct message {
	long mtype;
	score_t data;
};


int main(void)
{
	// genertate a key
	key_t key;
	int ret, msgid;
	struct message smsg;
	int len;

	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		exit(1);
	}

	//create a msessage queue id
	msgid = msgget(key, IPC_CREAT | 0600);
	if (msgid == -1) {
		perror("msgget");
		exit(1);
	}

	//send a message
	smsg.mtype = 8;
	strncpy(smsg.data.name, "abc", 4);
	smsg.data.avg = 99.9;
	len = sizeof(struct message) - sizeof(long); 

	ret = msgsnd(msgid, &smsg, len, 0);
	if (ret == -1) {
		perror("msgsnd");
		exit(1);
	}

	exit(0);
}

