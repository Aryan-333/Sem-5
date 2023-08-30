#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

// int main()
// {
//     pidd_t pid;
//     char *message;
//     int n;
//     printf("fork program starting\n");
//     pid = fork();
//     switch (pid)
//     {
//     case -1:
//         perror("fork failed");
//         exit(1);
//     case 0:
//         message = "This is the child";
//         n = 5;
//         break;
//     default:
//         message = "This is the parent";
//         n = 3;
//         break;
//     }
//     for (; n > 0; n--)
//     {
//         puts(message);
//         sleep(1);
//     }
//     exit(0);
// }

// int main()
// {
//     int status;
//     pid_t pidd;
//     pidd = fork();
//     if (pidd == -1)
//         printf("\nERROR child not created");
//     else if (pidd == 0) /* child process */
//     {
//         printf("\n I'm the child!");
//         exit(0);
//     }
//     else /* parent process */
//     {
//         wait(&status);
//         printf("\n I'm the parent!");
//             printf("\n Child returned: %d\n", status);
//     }
// }

int main()

    {
        pid_t pid;
        /* fork another process */
        pid = fork();
        if (pid < 0)
        { /* error occurred */
            fprintf(stderr, "Fork Failed");
            exit(-1);
        }
        else if (pid == 0)
        { /* child process */
            execlp("/bin/ls", "ls", NULL);
        }
        else
        { /* parent process */
            /* parent will wait for the child to complete */
            wait(NULL);
            printf("Child Complete\n");
            exit(0);
        }
    }
