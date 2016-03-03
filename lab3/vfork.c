#include <unistd.h>
#include <sys/types.h>
#include <stdio.h> 
#include <string.h> 

int main(void) 
{ 
    pid_t pid; 
	char c[50];
	int i=0,j;
	scanf("%s",c);
	pid = vfork();
	if(pid == 0){
		for(j=0;j<strlen(c);j++)
			if(c[j] == 'a' ||c[j] == 'e' ||c[j] == 'i' ||c[j] == 'o' ||c[j] == 'u' )
				i++;
	printf("%d",i);
	_exit(0);
}
return 0;
}
