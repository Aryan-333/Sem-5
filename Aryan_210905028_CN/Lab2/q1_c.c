#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORTNO 9999

int main()
{
    int len;
    char ch[100];
    int n, arr[100];
    struct sockaddr_in add;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr("127.0.0.1");
    add.sin_port = htons(PORTNO);

    len = sizeof(add);
    int result = connect(sockfd, (struct sockaddr *)&add, len);

    while (1)
    {
        printf("Enter the size of array:\n");
        scanf("%d", &n);

        printf("Enter the array:\n");
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &arr[i]);
        }

        write(sockfd, &n, sizeof(int));
        write(sockfd, arr, n * sizeof(int));

        int pid;

        read(sockfd, &pid, sizeof(int));
        read(sockfd, arr, n * sizeof(int));

        printf("Sorted Array\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d", arr[i]);
        }
        printf("\nProcess ID: %d\n", pid);
    }
}