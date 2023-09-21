#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORTNO 9999

void bubblesort(int n, int arr[])
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int len;
    struct sockaddr_in cliaddr, seraddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    seraddr.sin_port = htons(PORTNO);

    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));

    listen(sockfd, 5);

    while (1)
    {

        printf("Server is waiting\n");
        int clilen = sizeof(clilen);
        int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);

        if (fork() == 0)
        {
            int size;
            read(newsockfd, &size, sizeof(size));
            int arr[size];
            read(newsockfd, arr, sizeof(arr));

            bubblesort(size, arr);

            int id = getpid();

            write(newsockfd, &id, sizeof(id));
            write(newsockfd, &arr, sizeof(arr));
        }
    }
}