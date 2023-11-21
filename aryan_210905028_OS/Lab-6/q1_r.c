#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msg_st
{
    long int my_msg_type;
    char text[BUFSIZ];
};

int isPal(char num[])
{
    int i = 0;
    int n = strlen(num);
    while (num[i] != '\0')
    {
        if (num[i] != num[n - i - 1])
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int main()
{
    int running = 1;
    struct my_msg_st some_data;

    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    while (running)
    {
        if (msgrcv(msgid, (void *)&some_data, BUFSIZ, 0, 0) == -1)
        {
            fprintf(stderr, "msgrcv failed with error : % d\n", errno);
            exit(EXIT_FAILURE);
        }
        if (strncmp(some_data.text, "end", 3) == 0)
        {
            break;
        }
        if (isPal(some_data.text))
        {
            printf("%s is a Palindrome\n", some_data.text);
        }
        else
        {
            printf("%s is not a Palindrome\n", some_data.text);
        }
    }
    if (msgctl(msgid, IPC_RMID, 0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}