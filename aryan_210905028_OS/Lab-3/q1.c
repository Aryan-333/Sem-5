//Write a C program to block a parent process until the child completes using a wait system call.
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int status;
    pid_t pidd;
    pidd = fork();
    if (pidd == -1)
        printf("\nERROR child not created");
    else if (pidd == 0) 
    {
        printf("\n I'm the child!");
        exit(0);
    }
    else 
    {
        wait(&status);
        printf("\n I'm the parent!");
            printf("\n Child returned: %d\n", status);
    }
}