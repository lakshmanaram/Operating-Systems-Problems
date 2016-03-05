//type '/' to exit the server process without force closing
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE     50
void die(char *s)
{
	// process dies with character sequence as error
	perror(s);
	exit(1);
}
int main()
{
	int shmid,i;
	key_t key;
	char *shm;

	key = 5682;			//random shm key that should be equal to the one used in client code
	if ((shmid = shmget(key, MAXSIZE, IPC_CREAT | 0666)) < 0)	// creating shared memory
		die("shmget");

	struct shmid_ds * info = malloc(sizeof(struct shmid_ds));
	//data structure found in <sys/shm.h> that can be used to gain info about the shared memory and parent process programmatically
	int ab = shmctl(shmid,IPC_STAT,info);		// ab = -1 indicates error
	pid_t p = info->shm_cpid;					//process id
	time_t t = info -> shm_atime;				//time created
	printf("shmid %d \n%d\n",shmid,ab);
	printf("process %d\n",p);
	printf("Last attach time %ti \n",t);

	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)	// shmid, shmaddr = NULL - system chooses unused memory space, and shmflag
		die("shmat");

	//shm points to the first memory address of shared memory
	while(1){
		printf("Server Process: ");
		char a[50];
		scanf("%s",a);

		if(a[0]=='/')
			break;
		//quit the loop for detach and deleting shared memory to function.

		strcpy(shm+1,a);
		//writes the string onto shared memory starting from the second character
		*shm = '#';
		/*
		* puts '#' in the beginning indicating that
		* the server process has written some text
		*/
		while (*shm != '*')
		sleep(1);
		/*
		* Wait until the other process
		* changes the first character of our memory
		* to '*', indicating that it has read what
		* we put there.
		*/
		printf("Client Process: ");
		puts(shm+1);							// prints th eline written by the client process
//		putchar('\n');
	}
	shmdt(shm);
	shmctl(shmid,IPC_RMID,NULL);
	exit(0);
}
