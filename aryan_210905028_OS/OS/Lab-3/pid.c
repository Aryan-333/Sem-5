#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid;
    pid = fork();
    switch (pid)
    {
    case -1:
        printf("Error");
        exit(-1);
        break;
    case 0:
        printf("CHILD PROCESS\n Child Id:%d\n Parent Id:%d\n Process Id:%d\n", pid, getppid(), getpid());
        exit(0);
    default:
        printf("PARENT PROCESS\n Child Id:%d\n Parent Id:%d\n Process Id:%d\n", pid, getppid(), getpid());
        exit(0);

        break;
    }
}