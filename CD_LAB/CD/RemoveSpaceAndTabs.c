#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fptr1, *fptr2;
    char filename[30], c;
    printf("Enter the file name: ");
    scanf("%s", filename);

    fptr1 = fopen(filename, "r");

    if (fptr1 == NULL)
    {
        printf("Cannot open file\n");
        exit(0);
    }

    printf("Enter the resultant file name: ");
    scanf("%s", filename);

    fptr2 = fopen(filename, "w+");

    c = fgetc(fptr1);

    while (c != EOF)
    {
        if (c == ' ' || c == '\t')
        {
            fputc(c, fptr2);
            c = fgetc(fptr1);
            while (c == ' ' || c == '\t')
            {
                c = fgetc(fptr1);
            }
        }
        else
        {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
    }

    fclose(fptr1);
    fclose(fptr2);
}