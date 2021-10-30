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

struct mesg_buffer {
    long mesg_type;
    char mesg_text[6000];
}message;

void printArray(int numberArray[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d \n", numberArray[i]);
}

float avg(int numberArray[], int size) {
    int average = 0;
    int total = 0;
    for (int i = 0; i < size; i++) {
        total += numberArray[i];
    }
    average = total / (float)(size);
    return average;
}
float avgRange(int numberArray[], int size, int start, int end) {
    int average = 0;
    int total = 0;
    for (int i = 0; i < size; i++) {
        if (start <= numberArray[i] && end >= numberArray[i]) {
            total += numberArray[i];
        } else {
            continue;
        }
    }
    average = total / (float)(size);
    return average;
}
int countArray(int numberArray[], int size) {
    return size;
}
int max(int numberArray[], int size) {
    int max = numberArray[0];
    for (int i = 1; i < size; i++) {
        if (max < numberArray[i]) {
            max = numberArray[i];
        }
    }
    return max;
}
// int range(int numberArray[], int size)
// {

// }

int main(int argc, char * argv[]) {
    int noArg = 0;
    FILE * intFile;
    key_t key;
    int msgid;

    if (argc < 3) {
        printf("Number of files should be at least 1\n");
        exit(1);
    } else if (argc > 12) {
        printf("Number of files should be at most 10\n");
        exit(1);
    }
    noArg = atoi(argv[1]);
    if (noArg < 1 || noArg > 10) {
        printf("Number of files as N should be between 1 an 10\n");
        exit(1);
    }

    int * numberArray = (int * ) malloc(1000000 * sizeof(int));
    int count = 0;
    for (int i = 0; i < noArg; i++) {
        intFile = fopen(argv[i + 2], "r");
        if (intFile == NULL) {
            printf("File cannot be opened\n");
            exit(1);
        } else {
            int number = 0;

            while (!feof(intFile)) {
                fscanf(intFile, "%d", &number);
                numberArray[count] = number;
                count++;
            }
        }
    }

    key = ftok("/home/asuman/Desktop/os pj1/Project1.pdf", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    while (message.mesg_text != "exit") {

        pid_t pid;
        for (int i = 0; i < noArg; i++) {
            pid = fork(); 
            if (pid == 0) {
       		msgrcv(msgid, & message, sizeof(message), 1, 0);
            	printf("Data Received is : %s \n", message.mesg_text);
                if ((key = ftok("/home/asuman/Desktop/os pj1/Project1.pdf", i)) == (key_t) - 1) {
                    perror("IPC error: ftok");
                    exit(1);
                }
                msgid = msgget(key, 0666 | IPC_CREAT);
                message.mesg_type = 1;
		int countresult = countArray(numberArray,count);	
		char str[100];
		sprintf(str, "%d", countresult);
                strcpy(message.mesg_text, str);
                printf("message.mesg_text: %s\n", message.mesg_text);
                msgsnd(msgid, & message,
                    sizeof(message), 0);
                printf("Data send is: %s\n", message.mesg_text);
                _exit(0);
            } else {
                printf("parent process");
            }
            for (int i = 0; i < noArg; i++) {
                wait(NULL);
            }
        }
    }
    msgctl(msgid, IPC_RMID, NULL);
    free(numberArray);
    return 0;
}
