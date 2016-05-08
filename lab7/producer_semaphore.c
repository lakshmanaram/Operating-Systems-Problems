#include <stdio.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>                         // for malloc
#include <semaphore.h>                      // for semaphore
#define SEMPTY "empty"
#define SFULL "full"
#define SMUTEX "mutex"
sem_t *empty, *full, *mutex;
struct msgbuf {
long mtype;
int item;
};
int main(){
	key_t key;
	int msqid;
	struct msgbuf temp;
	key = 5663;
	msqid = msgget(key, 0666 | IPC_CREAT);
	int a,n;
	printf("Enter the number of buffers: ");
    scanf("%d",&n);
	sem_unlink(SEMPTY);
	sem_unlink(SFULL);
	sem_unlink(SMUTEX);
	empty = sem_open(SEMPTY,O_CREAT,0666,n);
    full = sem_open(SFULL,O_CREAT,0666,0);
    mutex = sem_open(SMUTEX,O_CREAT,0666,1);
	long mt = 1;
	while(1){
        printf("\nEnter an integer to produce:   ");
        int next_produced;
        scanf("%d",&next_produced);
        printf("%d is produced\n",next_produced);
        printf("Waiting for empty buffer\n");
        sem_wait(empty);
        sem_wait(mutex);
		temp.mtype = mt;
		temp.item = next_produced;
		a = msgsnd(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), 0);
        printf("%d is added to the buffer\n",next_produced);
		mt++;
        if(mt == n+1)
            mt=n;
        sem_post(mutex);
        sem_post(full);
    }
	msgctl(msqid, IPC_RMID, NULL);
    return 0;
}
