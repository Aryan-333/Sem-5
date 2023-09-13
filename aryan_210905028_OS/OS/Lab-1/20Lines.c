#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd = 0, i = 0, k = 0, p = 0;
    char ch[100], c;

    if (argc < 2)
    {
        printf("Insufficient Arguments");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error in file Opening");
        exit(1);
    }

    while ((read(fd, &c, 1)) > 0)
    {
        if (c != '\n')
        {
            ch[i] = c;
            i++;
        }
        else
        {
            k++;
            p++;
            ch[i] = '\0';
            i = 0;

            printf("Line: %d -- %s\n", p, ch);

            if (k == 20)
            {
                fgetc(stdin);
                k = 0;
            }
        }
    }
    if (i > 0)
    {
        p++;
        ch[i] = '\0';
        printf("Line: %d -- %s\n", p, ch);
    }
    close(fd);
    return 0;
}