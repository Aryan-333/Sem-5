#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#define FIFO_NAME "/tmp/my_fifo"
#define BUFFER_SIZE PIPE_BUF
int main()
{
	int pipe_fd;
	int res1,res2,res3,res4,i;
	int open_mode = O_RDONLY;
	int a,b,c,d;
	int bytes_read = 0;
	printf("Process %d opening FIFO O_RDONLY\n", getpid());
	pipe_fd = open(FIFO_NAME, open_mode);
	printf("Process %d result %d\n", getpid(), pipe_fd);
	if (pipe_fd != -1) {
		res1 = read(pipe_fd , &a, sizeof(int));
		res2 = read(pipe_fd , &b, sizeof(int));
		res3 = read(pipe_fd , &c, sizeof(int));
		res4 = read(pipe_fd , &d, sizeof(int));
		(void)close(pipe_fd);
	}
	else {
	exit(EXIT_FAILURE);
	}
	printf("Process %d finished\n", getpid());
	printf("The numbers are: %d %d %d %d\n",a,b,c,d);
	exit(EXIT_SUCCESS);
}