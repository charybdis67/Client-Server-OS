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
	key_t key;
    int msgid;
    key = ftok("progfile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1;
    printf("Enter command: ");
    fgets(message.mesg_text,MAX,stdin);
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("Data send is : %s \n", message.mesg_text);
    return 0;
}