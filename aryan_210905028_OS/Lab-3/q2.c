//Write a C program to load the binary executable of the previous program in a child process using the exec system call.

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
         
        printf("\nI'm the childgg!");
        printf("\nhanuman");


        execlp("./q1","q1",NULL);
    }
    else 
    {
        wait(&status);
        printf("\n I'm the parent!");
        printf("\n hello");

            printf("\n Child returned: %d\n", status);
    }
}