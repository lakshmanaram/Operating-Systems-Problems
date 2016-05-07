// Critical section problem using binary seamphore with busy wait Process 2
#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#define SMUTEX "mutex"
sem_t *mutex;
int main(){ 
    mutex = sem_open(SMUTEX,0);
    char choice;
    while(1){
        printf("Do you want to try entering the Critical Section ? (y) ");
        scanf(" %c",&choice);
        if(choice == 'y'){
            printf("Trying to enter the critical section\n");
            sem_wait(mutex);
            printf("In the critical section\n");
            do{
                printf("Wanna leave the Critical section? ");
                scanf(" %c",&choice);
            }while(choice != 'y');
            sem_post(mutex);
            printf("Left the Critical section\n");
        }
    }
    return 0;
}
