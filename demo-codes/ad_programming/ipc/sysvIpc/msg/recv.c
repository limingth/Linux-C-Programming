#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define KEYPATH "/etc/passwd"
#define KEYID 123

typedef struct {
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
	int ret, msgid = 0;
	struct message smsg;
	int len;
	struct msqid_ds buf;
#if 1
	key = ftok(KEYPATH, KEYID);
	if (key == -1) {
		perror("ftok");
		exit(1);
	}

	//get a msessage queue id
	msgid = msgget(key, IPC_CREAT | 0600);
	if (msgid == -1) {
		perror("msgget");
		exit(1);
	}

#endif	
	ret = msgctl(msgid, IPC_STAT, &buf);
	if (ret == -1) {
		perror("msgctl");
		exit(1);
	}

	if (buf.msg_qnum == 0) {
		ret = msgctl(msgid, IPC_RMID, NULL);
		if (ret == -1) {
			perror("msgctl");
			exit(1);
		}
		exit(0);
	}

	len = sizeof(smsg);
	ret = msgrcv(msgid, &smsg, len, 8, 0);
	if (ret == -1) {
		perror("msgrcv");
		exit(1);
	}

	printf("name=%s\n", smsg.data.name);
	printf("score avg= %f\n", smsg.data.avg);
	

	exit(0);
}

