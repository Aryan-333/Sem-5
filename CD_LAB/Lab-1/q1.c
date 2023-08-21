// To count the number of lines and characters in a file.

#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fptr1;
char filename[100], c;
int characters=0,line=1;
printf("Enter the filename to open for reading: \n");
scanf("%s", filename);
fptr1 = fopen(filename, "r");
// Open one file for reading

if (fptr1 == NULL)
{
printf("Cannot open file %s \n", filename);
exit(0);
}

// Read contents from file
while (c != EOF)
{
	c = fgetc(fptr1);
	if ( c == '\n')
	{
		line++;
	}
	else{
		characters++;
	}
}

printf("\nTotal Characters= %d and Total lines= %d", characters,line);
fclose(fptr1);
return 0;
}