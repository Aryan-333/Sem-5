/*Write a TCP concurrent client server program where server accepts integer array from
client and sorts it and returns it to the client along with process id.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int main()
{
    int sockfd, nsockfd, length, n;
    struct sockaddr_in seraddress, cliaddr;
    int arr[20];
    int arr_size = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddress.sin_family = AF_INET;
    seraddress.sin_addr.s_addr = INADDR_ANY;
    seraddress.sin_port = htons(10200);

    bind(sockfd, (struct sockaddr *)&seraddress, sizeof(seraddress));

    listen(sockfd, 5);

    length = sizeof(cliaddr);

    while (1)
    {
        nsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, &length);
        printf("Connected to client");

        if (fork() == 0)
        {
            close(sockfd);
            int pid = getpid();
            n = read(nsockfd, &arr_size, sizeof(int));
            n = read(nsockfd, arr, arr_size * sizeof(int));
            // Sorting the array
            qsort(arr, arr_size, sizeof(int), cmpfunc);

            n = write(nsockfd, &pid, sizeof(int));
            n = write(nsockfd, arr, arr_size * sizeof(int));

            getchar();

            close(nsockfd);
        }
    }
}