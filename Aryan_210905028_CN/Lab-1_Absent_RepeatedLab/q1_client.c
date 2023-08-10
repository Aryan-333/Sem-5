#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int main()
{
	int soc_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in add;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = inet_addr("127.0.0.1");
	add.sin_port = htons(10200);
	int result = connect(soc_id, (struct sockaddr *)&add, sizeof(add));
	if (result == -1)
	{
		perror("\n There is a client Error");
		exit(1);
	}

	int n = 1;
	char text[256];
	char changed[256];

	printf("\nEnter the message: ");
	scanf("%s", text);

	for (int i = 0; i < strlen(text); i++)
	{
		changed[i] = text[i] + 4;
	}

	write(soc_id, changed, sizeof(changed));
}
