#include <unistd.h>
#include <sys/types.h>
#include <stdio.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

int main(){
	char c[50];
	scanf("%s",c);
	int a = 0;
	a = open(c,O_DIRECTORY);
	if(a>0){
		DIR * h = opendir(c);
		struct dirent *b = readdir(h);
		int i = 0;
		while(b){
			i++;
			printf("%s \n",b -> d_name);
			b = readdir(h);
		}
		printf("%d files",i);
		closedir(h);
	}
	else
		printf("file");

	return 0;
}
