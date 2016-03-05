#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    while(1){
        int c,a,b;
        scanf("%d",&c);
        switch(c){
            case 1:
                a = open("tst1.txt",O_CREAT|O_WRONLY|O_TRUNC,O_RDWR);
                write(a,"hello",6);
                close(a);
                break;
            case 2:
                a = open("tst1.txt",O_RDONLY);
                b = open("tst2.txt",O_CREAT|O_WRONLY|O_TRUNC,O_WRONLY);
                char buf[200];
                read(a,buf,200);
                write(b,buf,6);
                close(a);
                close(b);
                break;
            case 3:
                link("tst1.txt","tst2.txt");
                break;
            case 4:
                unlink("tst1.txt");
                unlink("tst2.txt");
                break;
            default:
                printf("Not valid");
        }
    }
    return 0;
}
