// Write a program to print the lines of a file that contain a word given as the program argument (a simple version of grep UNIX utility).
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

void main(int argc,char* argv[])
{
    if(argc < 3)
    {
        printf("Insufficient Arguments\n");
        exit(1);
    }
    int fd=open(argv[2],O_RDONLY);
    if(fd==-1)
    {
        printf("File Not Found\n");
        exit(1);
    }
    char c,temp[200];
    int i=0,k=0;
    while(read(fd,&c,1)>0)
    {
        if(c!='\n')
        {
            temp[i++]=c;
        }
        else
        {
            k++;
            temp[i]='\0';
            i=0;
            if(strstr(temp,argv[1]))
            {
                printf("Line:%d \t %s \n", k,temp);
            }
        }
    }
    exit(0);
}