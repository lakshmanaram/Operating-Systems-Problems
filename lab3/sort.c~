#include <unistd.h>
#include <sys/types.h>
#include <stdio.h> 

int main(void) 
{ 
    pid_t   pid; 
    int     i,j; 
    printf("Parent Process starts \n");
    int n;
	scanf("%d",&n);
	int arr[50];
	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);
    if ((pid = fork()) < 0) { 
        printf("fork error"); 
    } else if (pid == 0) {     
		printf("Inside Child Process : \n"); 
		for(i=0;i<n;i++)
			for(j = i;j>0;j--)
				if(arr[j] > arr[j-1]){
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
				}
		printf("Sorted array :\n");
		for(i = 0; i < n; i++){
			printf("%d ",arr[i]);	
		}
		printf("\n");
    } else{
		printf("Inside Parent Process : \n");
		for(i=0;i<n;i++)
			for(j = i;j>0;j--)
				if(arr[j] < arr[j-1]){
					int temp = arr[j];
					arr[j] = arr[j-1];
					arr[j-1] = temp;
				}
		printf("Sorted array :\n");
		for(i = 0; i < n; i++){
			printf("%d ",arr[i]);	
		}
		printf("\n");
	}
} 
