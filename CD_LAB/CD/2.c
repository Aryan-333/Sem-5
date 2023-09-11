#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *f1, *f2;
    char filename[100], c;

    // printf("enter the file name to be opened");
    // scanf("%s", filename);

    f1 = fopen("Test.txt", "r");

    if (f1 == NULL)
    {
        printf("cannot open the file\n");
        exit(0);
    }
    // printf("enter the file name to be made");
    // scanf("%s", filename);
    f2 = fopen("prerem.txt", "w+");

    int main_flag = 0;
    int mlc_flag = 0;
    char line[10000];
    while (fgets(line, sizeof(line), f1))
    {
        char *main = strstr(line, "main");
        if (main != NULL)
        {
            main_flag = 1;
        }
        int insideQuote = 0;

        for (int i = 0; i < strlen(line); i++)
        {

            if (line[i] == '"')
            {
                insideQuote = !insideQuote;
            }
            if (line[i] == '/' && line[i + 1] == '/' && insideQuote == 0)
            {
                do
                {
                    i++;
                } while (line[i] != '\n');
            }
            else if (line[i] == '/' && line[i + 1] == '*' && insideQuote == 0)
            {
                do
                {
                    i++;
                    if (line[i] == '\n')
                    {
                        mlc_flag = 1;
                        break;
                    }
                } while (line[i] != '*' && line[i + 1] != '/');
            }
            if (mlc_flag == 1)
            {
                while (line[i] != '\n')
                {
                    i++;
                    if (line[i] == '*' && line[i + 1] == '/')
                    {
                        mlc_flag = 0;
                        break;
                    }
                }
                break;
            }

            if (main_flag == 1)
            {
                fputc(line[i], f2);
            }
            else
            {
                if (line[i] == '#')
                {
                    do
                    {
                        i++;
                    } while (line[i] != '\n');
                }
            }
        }
    }
    fclose(f1);
    fclose(f2);
}