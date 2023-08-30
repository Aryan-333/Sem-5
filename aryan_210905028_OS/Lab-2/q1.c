/* Write a C program to emulate the ls -l UNIX command that prints all files in a
current directory and lists access privileges, etc. DO NOT simply exec ls -l from the
program. */ 

#include<unistd.h>
#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<sys/stat.h>
#include<stdlib.h>

void main()
{

    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp=opendir(".");
    if(!dp)
    {
        fprintf(stderr,"Cannot open directory :\n");
        exit(0);
    }
    while(entry=readdir(dp))
    {
        lstat(entry->d_name,&statbuf);
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0)
        {
            continue;
        }
        printf("%s\t\t\t",entry->d_name);

            printf(S_ISDIR(statbuf.st_mode)  ? "d\t" : "-\t");

        printf(statbuf.st_mode & S_IRUSR ? "r" : "-");
        printf(statbuf.st_mode & S_IWUSR ? "w" : "-");
        printf(statbuf.st_mode & S_IXUSR ? "x" : "-");
        printf(statbuf.st_mode & S_IRGRP ? "r" : "-");
        printf(statbuf.st_mode & S_IWGRP ? "w" : "-");
        printf(statbuf.st_mode & S_IXGRP ? "x" : "-");
        printf(statbuf.st_mode & S_IROTH ? "r" : "-");
        printf(statbuf.st_mode & S_IWOTH ? "w" : "-");
        printf(statbuf.st_mode & S_IXOTH ? "x" : "-");
        printf("\n");
    }
    closedir(dp);
}