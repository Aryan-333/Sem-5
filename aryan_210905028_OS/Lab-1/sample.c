#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

// size_t write(int fildes, const void *buf, size_t nbytes);

//Writing data

// int main()
// {
// if ((write(1, "Here is some data\n", 18)) != 18)
// write(2, "A write error has occurred on file descriptor 1\n",46);
// return 0;
// }


//read and displaying
int main()
{
char buffer[128];
int nread;
nread = read(0, buffer, 128);
if (nread == -1)
write(2, "A read error has occurred\n", 26);
if ((write(1,buffer,nread)) != nread)
write(2, "A write error has occurred\n",27); 
return 0;
}

//read from file and displaying on terminal
int main()
{
	int in;
	char buffer[100];

	int nread;
	nread = read(0, buffer, 100);
	in = open("test.txt",O_RDONLY);
	int size=read(in,buffer,100);
	printf("The substring is: %s\n", letter);
	write(1,buffer,size);

return 0;