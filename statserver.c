/*
	@author: Asuman Aydın
	@date 28.10.21
	project1
*/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MAX 10
struct mesg_buffer{
	long mesg_type;
	char mesg_text[6000];
} message;

// void requests()
// {
// // 	The request “count” is to find the number all integers in the whole data set.
// // The request “avg” is to find the average of all integers in the whole data set. The
// // request “count <start><end>” is to find the number of integers in range [<start>,
// // <end>], inclusive. The request “avg <start><end>” is to find the average of all
// // integers in range [<start>, <end>]. The request “range <start> <end> <K>” is to
// // find the top <K> integers in range [<start>, <end>] in ascending order. In this
// // request, <K> is the maxiumum number of integers to return. If the [<start>, <end>]
// // has more integers than <K>, only <K> largest of them will be returned in ascending
// // sorted order. <K> can be at most 1000, and at least 1.
// }

// void printArray(int A[], int size) 
// { 
//     int i; 
//     printf(size);
//     printf("\n"); 
//     for (i=0; i < size; i++) 
//         printf("%d ", A[i]); 
//     printf("\n"); 
// } 

int main(int argc, char *argv[])
{
	// int noArg = 0;
	// FILE *intFile;

	// if(argc < 3)
	// {
	// 	printf("Number of files should be at least 1\n");
	// 	exit(1);
	// }
	// else if(argc > 12 )
	// {
	// 	printf("Number of files should be at most 10\n");
	// 	exit(1);
	// }

	// noArg = argv[1];
	// if(noArg < 1 || noArg > 10)
	// {
	// 	printf("Number of files as N should be between 1 an 10\n");
	// 	exit(1);
	// }

	// int * numberArray = (int *)malloc(1000000*sizeof(int));
	// for(int i = 0; i < noArg; i++)
	// {
	// 	intFile = fopen(argv[i+2],"r");
	// 	if(intFile == NULL)
	// 	{
	// 		printf("File cannot be opened\n");
	// 		exit(1);
	// 	}
	// 	else
	// 	{
	// 		fscanf(intFile, "%1d", &numberArray[i]);
	// 	}
	// }

	// printArray(numberArray, sizeof(numberArray));


    key_t key;
    int msgid;
  
    // ftok to generate unique key
    key = ftok("/home/asuman/Desktop/os pj1/Project1.pdf", 65);
  
    // msgget creates a message queue
    // and returns identifier
    msgid = msgget(key, 0666 | IPC_CREAT);
  
    // msgrcv to receive message
    msgrcv(msgid, &message, sizeof(message), 1, 0);
  
    // display the message
    printf("Data Received is : %s \n", 
                    message.mesg_text);
  
    // to destroy the message queue
    msgctl(msgid, IPC_RMID, NULL);
  
    return 0;
}
