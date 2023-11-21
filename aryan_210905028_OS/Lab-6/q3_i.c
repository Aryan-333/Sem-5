#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <sys/msg.h>

struct my_msg
{
    long int msg_type;
    char text[512];
};

int main()
{
    struct my_msg data;
    char buffer[BUFSIZ];

    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if (msgid == -1)
    {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        printf("Enter String : \t");
        scanf(" %s", buffer);
        data.msg_type = 1;
        strcpy(data.text, buffer);
        if (msgsnd(msgid, (void *)&data, 512, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0)
        {
            break;
        }
    }
    exit(EXIT_SUCCESS);
}