#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 27
void die(char *s)
{
	perror(s);
	exit(1);
}
int main()
{
	int shmid;
	key_t key;
	char *shm, *s;
	key = 5682;
	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)
		die("shmget");
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
		die("shmat");
	while(1){
		printf("Server Process: %s\n",shm + 1);
		printf("Client Process : ");
		char *a = (char *)malloc(MAXSIZE);
		int i;
		scanf(" %s",a);
		strcpy(shm,"*");
		strcat(shm,a);
		while (*shm != '#')
			sleep(1);
	}
	shmdt(shm);
	return 0;
}

