//That merges lines alternatively from 2 files and stores it in a resultant file.

#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fptr1, *fptr2, *fptr3;
int flag=1;

char filename[100], c1,c2;
int linecount=1;
printf("Enter the first filename: \n");
scanf("%s", filename);
fptr1 = fopen(filename, "r");
// Open one file for reading

if (fptr1 == NULL)
{
printf("Cannot open file %s \n", filename);
exit(0);
}

printf("Enter the second filename: \n");
scanf("%s", filename);
fptr2 = fopen(filename, "r");
// Open one file for reading

if (fptr2 == NULL)
{
printf("Cannot open file %s \n", filename);
exit(0);
}

printf("Enter the filename to open for writing: \n");
scanf("%s", filename);
fptr3 = fopen(filename, "w+");



while(flag==1){
	while (c1 != EOF)
{
	c1 = fgetc(fptr1);
	if ( c1 == '\n')
	{
		break;
	}
	fputc(c1,fptr3);
}
fputc('\n',fptr3);
while (c2 != EOF)
{
	c2 = fgetc(fptr1);
	if ( c2 == '\n')
	{
		break;
	}
	fputc(c2,fptr3);
}
fputc('\n',fptr3);
if(c1==EOF && c2==EOF){
	flag=0;
}
}


printf("\n");


fclose(fptr1);
fclose(fptr2);
fclose(fptr3);
return 0;
}