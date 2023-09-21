#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORTNO 9999

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
        char buf[100];
        printf("Server is waiting\n");
        int clilen = sizeof(clilen);
        int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        int n = read(newsockfd, buf, sizeof(buf));
        printf("Encrypted Message%s\n", buf);

        for (int i = 0; i < buf[i] != '\0'; i++)
        {
            buf[i] -= 4;
        }
        printf("Decrypted Message%s\n", buf);
    }
}