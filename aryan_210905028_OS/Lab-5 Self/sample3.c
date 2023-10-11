#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
int main()
{
    int res = mkfifo("my_fifo", 0777); /*0777 represents the permission mode for the FIFO. 
                                        It's given in octal notation. 0777 means that the FIFO is readable, 
                                        writable, and executable by everyone.*/
    if (res == 0)
        printf("FIFO created\n");
    exit(EXIT_SUCCESS);
}