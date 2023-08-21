//To reverse the file contents and store in another file. Also display the size of file using file handling function.

#include <stdio.h>
#include <stdlib.h>

int main()
{
FILE *fptr1, *fptr2;
char filename[100], c;
printf("Enter the filename to open for reading: \n");
scanf("%s", filename);
fptr1 = fopen(filename, "r");
// Open one file for reading

if (fptr1 == NULL)
{
printf("Cannot open file %s \n", filename);
exit(0);
}

printf("Enter the filename to open for writing: \n");
scanf("%s", filename);
fptr2 = fopen(filename, "w+");
c = fgetc(fptr1);
// Read contents from file


fseek(fptr1, 0, SEEK_END);
long fileSize = ftell(fptr1);
fseek(fptr1, 0, SEEK_SET);

char ch;
long pos = fileSize - 1;

while (pos >= 0) {
    fseek(fptr1, pos, SEEK_SET);
    ch = fgetc(fptr1);
    fputc(ch, fptr2);
    pos--;
}

printf("\n");

printf("\n Reversed Content copied to %s", filename);
printf("\n File Size is %ld", fileSize);


fclose(fptr1);
fclose(fptr2);
return 0;
}