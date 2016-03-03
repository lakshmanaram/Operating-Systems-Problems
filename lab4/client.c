#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE     50
void die(char *s)
{
	// process dies with character sequence as error
	perror(s);
	exit(1);
}
int main()
{
	int shmid;
	key_t key;
	char *shm, *s;

	key = 5682;								// same id as in server process

	if ((shmid = shmget(key, MAXSIZE, 0666)) < 0)
		die("shmget");
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
		die("shmat");

	while(1){
		s = shm;
		printf("Server Process: ");
		puts(s+1);								// prints the message in shared memory
		putchar('\n');
		printf("Client Process : ");
		char a[50];
		int i;
		scanf("%s",a);
		s = shm;
		s++;
		for(i=0;a[i]!='\0';i++){
			*(s++) = a[i];
		}
		*s++ = '\0';
		*shm = '*';
		/*
		* puts '*' in the beginning indicating that
		* the server process has written some text
		*/
		if(a[0]=='/')
			break;									// exiting the client process
		while (*shm != '#')
			sleep(1);

		/*
		* Wait until the other process
		* changes the first character of our memory
		* to '#', indicating that it has read what
		* we put there.
		*/
	}
	shmdt(shm);
	exit(0);
}
