// type '/' to terminate both the server and the client process without having to force close
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>

struct msgbuf {
long mtype;				// message type
char mess[10];			// max of 8k+ bytes can be passed
};

int main(){
	key_t key;			// message queue key
	int msqid;			// message queue id
	struct msgbuf temp;
	key = 5663;
	msqid = msgget(key, 0666 | IPC_CREAT);	// getting message queue id

	// getting msg queue info programmatically
	struct msqid_ds *buf = (struct msqid_ds *)malloc(sizeof(struct msqid_ds));
	int a = msgctl(msqid, IPC_STAT, buf);
	printf("User id: %d Permission mode: %o\n",buf->msg_perm.uid,buf -> msg_perm.mode);

	while(1){
		// infinite loop until the input sttarts with '/'
		printf("Server Process : ");
		scanf("%s",temp.mess);
		temp.mtype = 1;
		// messages being sent has type '1'
		a = msgsnd(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), 0);
		if(temp.mess[0] == '/')
			break;
		printf("Client Process : ");

		a = 0;
		while(a==0)
			// wait until receiving a message with type 2
			a = msgrcv(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), 2, 0);
		printf("%s",temp.mess);
		putchar('\n');
	}
	msgctl(msqid, IPC_RMID, NULL);
	return 0;
}
