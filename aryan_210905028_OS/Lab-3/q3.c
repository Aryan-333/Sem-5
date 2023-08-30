// Write a program to create a child process. Display the process IDs of the process, parent and child (if any) in both the parent and child processes.

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
    pid_t pid;
    int status;
    pid = fork();
    switch (pid)
    {
    case -1:
        printf("Error occured!...\n");
        exit(-1);
    case 0:
        printf("Executing child process\n  Process ID: %d\n  Parent Process ID: %d\n  Child Process ID: %d\n    Exiting child process...\n\n\n",
               getpid(), getppid(), pid);
        exit(0);
    default:
        wait(&status);
        printf("Executing parent process...\n   Child Status has returned: %d\n   Process ID: %d\n   Parent Process ID: %d\n   child Process ID: %d\nNow, Exiting parent process...\n",
               status, getpid(), getppid(), pid);
    }
    return 0;
}