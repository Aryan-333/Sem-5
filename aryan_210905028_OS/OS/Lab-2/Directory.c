#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>

void printAll(char *dir, int depth)
{
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    dp = opendir(dir);
    if (!dp)
    {
        printf("Error!");
        exit(1);
    }

    chdir(dir);

    while (entry = readdir(dp))
    {
        lstat(entry->d_name, &statbuf);
        for (int i = 0; i < depth; i++)
        {
            printf(" ");
        }
        printf("%s", entry->d_name);
        printf("\n");
        if (S_ISDIR(statbuf.st_mode))
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }
            else
            {
                printAll(entry->d_name, depth + 1);
            }
        }
    }
    chdir("..");
    closedir(dp);
}

int main()
{
    printAll(".", 0);
    return 0;
}