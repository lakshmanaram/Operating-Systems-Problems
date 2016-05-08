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
    empty = sem_open(SEMPTY,0);
    full = sem_open(SFULL,0);
    mutex = sem_open(SMUTEX,0);
    long mt = 1;
	while(1){
        int next_produced;
        printf("Enter any character to consume: ");
        char c;
        scanf(" %c",&c);
        sem_wait(full);
        sem_wait(mutex);
        a = 0;
		a = msgrcv(msqid, &temp, sizeof(struct msgbuf) - sizeof(long), mt, 0);
        if(a!=-1){
            next_produced = temp.item;
            mt++;
        }
        if(mt == n+1)
            mt = n;
        sem_post(mutex);
        sem_post(empty);
        if(a!=-1)
            printf("Consumer Process consumed: %d\n",next_produced);
    }
    return 0;
}
