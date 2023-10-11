#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE 256//PIPE_BUF  //PIPE_BUF, which represents the maximum size of single write operation to a pipe.
#define TEN_MEG 256  //total amount of data (in bytes) that you want to send through the pipe. In this case, it's set to 10 megabytes.
int main()
{
    int pipe_fd;
    int res;
    int open_mode = O_WRONLY;
    int bytes_sent = 0;
    char buffer[BUFFER_SIZE + 1];

    if (access(FIFO_NAME, F_OK) == -1) /*checks if the named pipe specified by FIFO_NAME exists 
                                        (F_OK is a constant that checks for existence). If the pipe does not 
                                        exist (returns -1), it proceeds to create it.*/
    {
        res = mkfifo(FIFO_NAME, 0777);
        if (res != 0)
        {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
            exit(EXIT_FAILURE);
        }
    }

    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(FIFO_NAME, open_mode);
    printf("Process %d result %d\n", getpid(), pipe_fd);

    if (pipe_fd != -1)
    {
        while (bytes_sent < TEN_MEG)
        {
            res = write(pipe_fd, buffer, BUFFER_SIZE); //basically yaha buffer ke andar joh bhi hai joh write ho raha hai pipe_fd mei basically pipe mei taaki vha se consumer consume kar sakta hai
                                                        // iss sample mei hmara buffer empty hai
            if (res == -1)
            {
                fprintf(stderr, "Write error on pipe\n");
                exit(EXIT_FAILURE);
            }
            bytes_sent += res;
        }
        (void)close(pipe_fd);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    printf("Process %d finished\n", getpid());
    exit(EXIT_SUCCESS);
}