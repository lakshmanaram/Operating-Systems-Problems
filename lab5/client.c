// '/' input in server program terminates the client program.
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>

struct msgbuf {
long mtype;
char mess[10];
};

int main(){
	key_t key;		// message queue key
	int msqid;		// message queue id
	struct msgbuf temp;
	key = 5663;
	msqid = msgget(key, 0666 | IPC_CREAT);	// getting message queue id

	while(1){
		printf("Server Process : ");
		int a = 0;
		while(a==0)
			a = msgrcv(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), 1, 0);
		printf("%s\n",temp.mess);
		if(temp.mess[0] == '/')
			break;
		printf("Client Process : ");
		scanf("%s",temp.mess);
		temp.mtype = 2;
		a = msgsnd(msqid, &temp, sizeof(struct msgbuf) - sizeof(long),0);
	}
	return 0;
}
