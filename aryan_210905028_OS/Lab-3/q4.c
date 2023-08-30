/*Create a zombie (defunct) child process (a child with exit() call, but no
corresponding wait() in the sleeping parent) and allow the init process to adopt it
(after parent terminates). Run the process as a background process and run the “ps”
command.*/

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
        printf("Executing child process\nNow, Exiting child process\n");
        exit(0);
    default:
        sleep(5);
        printf("Executing parent process\n  Child Status has returned: %d\n  Now, Exiting parent process\n",
               status);
    }
    return 0;
}