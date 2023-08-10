#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORTNO 10200

int main()
{
	int soc_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in seradd;
	seradd.sin_family = AF_INET;
	seradd.sin_addr.s_addr = inet_addr("127.0.0.1");
	seradd.sin_port = htons(PORTNO);

	bind(soc_id, (struct sockaddr *)&seradd, sizeof(seradd));
	listen(soc_id, 5);

	int done = 0;
	while (!done)
	{
		char changed[256];
		char text[256];
		int client;
		struct sockaddr_in cliadd;
		int n = 1;
		int new_soc_id = accept(soc_id, (struct sockaddr *)&cliadd, &client);
		client = sizeof(client);

		n = read(new_soc_id, changed, sizeof(changed));
		for (int i = 0; i < strlen(changed); i++)
		{
			text[i] = changed[i] - 4;
		}
		printf("\nChanged Message: %s", changed);
		printf("\nOrignal Message: %s", text);
		done = 1;
	}
}
