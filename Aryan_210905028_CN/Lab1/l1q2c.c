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
    struct sockaddr_in add;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr("127.0.0.1");
    add.sin_port = htons(PORTNO);

    len = sizeof(add);
    int result = connect(sockfd, (struct sockaddr *)&add, len);

    while (1)
    {
        printf("Enter the string(\"Stop\" to stop):\n");
        gets(ch);
        ch[strlen(ch)] = '\0';

        write(sockfd, ch, strlen(ch));

        if (strcmp(ch, "Stop") == 0)
        {
            printf("Client terminated...\n");
            exit(0);
        }

        read(sockfd, ch, strlen(ch));
        printf("Resultant Sentence%s\n", ch);
    }
}