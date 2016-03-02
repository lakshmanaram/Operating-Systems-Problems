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
	key_t key;
	int msqid;
	struct msgbuf temp = {1,"heyya"};
	key = 5663;
	msqid = msgget(key, 0666 | IPC_CREAT);
	struct msqid_ds *buf = (struct msqid_ds *)malloc(sizeof(struct msqid_ds));
	int a = msgctl(msqid, IPC_STAT, buf);
	printf("User id: %d Permission mode: %o\n",buf->msg_perm.uid,buf -> msg_perm.mode);
	a = msgrcv(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), 2, 0);
	printf("%d\n",a);	
	printf("%s",temp.mess);
	return 0;
}
