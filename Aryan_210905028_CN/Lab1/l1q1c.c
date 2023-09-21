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

    printf("Enter the string");
    gets(ch);
    ch[strlen(ch)] = '\0';

    for (int i = 0; ch[i] != '\0'; i++)
    {
        ch[i] += 4;
    }
    write(sockfd, ch, sizeof(ch));
}