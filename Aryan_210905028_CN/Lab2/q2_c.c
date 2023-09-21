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
    char ch;
    float a, b;
    struct sockaddr_in add;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr("127.0.0.1");
    add.sin_port = htons(PORTNO);

    len = sizeof(add);
    int result = connect(sockfd, (struct sockaddr *)&add, len);

    while (1)
    {
        printf("Enter the first element\n");
        scanf("%f", &a);

        printf("Enter the second element\n");
        scanf("%f", &b);

        printf("Enter the operator:\n");
        scanf(" %c", &ch);

        write(sockfd, &a, sizeof(a));
        write(sockfd, &b, sizeof(b));
        write(sockfd, &ch, sizeof(ch));

        float res;

        read(sockfd, &res, sizeof(res));

        printf("\nResult: %f\n", res);
    }
}