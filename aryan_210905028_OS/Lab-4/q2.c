// Write a program to print out the complete stat structure of a file.

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

const char *perms(__mode_t mode)
{
    static char buf[16] = {0};
    int i = 0;
    // user permissions
    buf[i++] = ((mode & S_IRUSR) ? 'r' : '-');
    buf[i++] = ((mode & S_IWUSR) ? 'w' : '-');
    buf[i++] = ((mode & S_IXUSR) ? 'x' : '-');
    // group permissions
    buf[i++] = ((mode & S_IRGRP) ? 'r' : '-');
    buf[i++] = ((mode & S_IWGRP) ? 'w' : '-');
    buf[i++] = ((mode & S_IXGRP) ? 'x' : '-');
    // other permissions
    buf[i++] = ((mode & S_IROTH) ? 'r' : '-');
    buf[i++] = ((mode & S_IWOTH) ? 'w' : '-');
    buf[i++] = ((mode & S_IXOTH) ? 'x' : '-');
    return buf;
}

// char* c_time(time_t val){
//     return strftime("%d:%m:%y %H:%M:%S",localtime(&val));
// }

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Insufficient Arguments");
        return 0;
    }
    struct stat file_stat;
    stat(argv[1], &file_stat);

    printf("File: %s\n",argv[1]);
      printf("Inode: %ld\n", file_stat.st_ino);
      printf("Device Container ID: %ld\n", file_stat.st_dev);
      printf("Mode: %10.10s\n", perms(file_stat.st_mode));
      printf("Hard Links: %ld\n", file_stat.st_nlink);
      printf("User ID: %d\n", file_stat.st_uid);
      printf("Group ID: %d\n", file_stat.st_gid);
      printf("Device ID: %ld\n", file_stat.st_rdev);
      printf("Total Size: %ld\n", file_stat.st_size);
      printf("Block Size: %ld\n" , file_stat.st_blksize);
      printf("Number of blocks: %ld\n", file_stat.st_blocks);
      printf("Last Access Time: %ld\n", ctime(&file_stat.st_atime));
      printf("Last Modified: %ld\n", ctime(&file_stat.st_mtime));
      printf("Last Status: %ld\n",ctime(&file_stat.st_ctime));
    return 0;
}
