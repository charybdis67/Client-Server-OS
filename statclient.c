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

struct mesg_buffer{
	long mesg_type;
	char mesg_text[6000];
} message;


int main(int argc, char *argv[])
{
    struct timeval current_time, end_time;
    key_t key;
    int msgid;
    
    gettimeofday(&current_time, NULL);
    printf("micro seconds : %ld", current_time.tv_usec);

    key = ftok("/home/asuman/Desktop/os pj1/Project1.pdf", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    printf("Enter commands from these options --> avg, count, range, exit./n");
    while(message.mesg_text != "exit")
    {
        fgets(message.mesg_text,1000,stdin);
        msgsnd(msgid, &message, sizeof(message), 0);
    }
    msgrcv(msgid, & message, sizeof(message), 1, 0);
    printf("Data Received is : %s \n", message.mesg_text);
    printf("Client exited.");
    gettimeofday(&end_time, NULL);
    printf("micro seconds : %ld", end_time.tv_usec);
    exit(0);

    return 0;

}
