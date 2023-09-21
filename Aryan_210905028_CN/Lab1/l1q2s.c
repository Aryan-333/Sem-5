#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORTNO 9999

void removeDuplicates(char *sentence)
{
    char result[102] = "";
    char *token = strtok(sentence, " ");

    while (token != NULL)
    {
        if (strstr(result, token) == NULL)
        {
            strcat(result, token);
            strcat(result, " ");
        }
        token = strtok(NULL, " ");
    }
    strcpy(sentence, result);
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
        char buf[100];
        printf("Server is waiting\n");
        int clilen = sizeof(clilen);
        int newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        int n = read(newsockfd, buf, sizeof(buf));

        if (strcmp(buf, "Stop") == 0)
        {
            printf("\nServer terminated...");
            exit(0);
        }
        printf("\nMessage from client : %s", buf);

        removeDuplicates(buf);
        write(newsockfd, buf, sizeof(buf));
    }
}