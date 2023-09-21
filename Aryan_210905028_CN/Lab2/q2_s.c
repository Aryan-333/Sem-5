#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORTNO 9999

float calc(float a, float b, char ch)
{
    switch (ch)
    {
    case '+':
        return a + b;
        break;

    case '-':
        return a - b;
        break;

    case '*':
        return a * b;
        break;

    case '/':
        return a / b;
        break;
    }
}

int main()
{
    int len;
    float a, b;
    char ch;
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

            read(newsockfd, &a, sizeof(a));
            read(newsockfd, &b, sizeof(b));
            read(newsockfd, &ch, sizeof(ch));

            float res = calc(a, b, ch);

            write(newsockfd, &res, sizeof(res));
        }
    }
}