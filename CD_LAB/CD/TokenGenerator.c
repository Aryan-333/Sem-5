#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main_flag = 0;
int mlc_flag = 0;
int ind = 0;
int identifier_count = 0;

typedef struct
{
    char name[70];
    int row;
    int col;
    char type[70];
} Token;

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum",
                          "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static",
                          "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};

char SpecialSymbol[] = {'$', '[', ']', '{', '}', '(', ')', '.', ',', ':', ';', '?', '"', '\\'};

void displayToken(Token token[])
{

    int currentRow = -1;

    for (int i = 0; i < ind; i++)

    {
        if (token[i].row != currentRow)
        {
            printf("\n");
            currentRow = token[i].row;
        }
        printf("<%s, %s, %d, %d>  ", token[i].name, token[i].type, token[i].row, token[i].col);
    }
    printf("\n");
}

void removepreandcom(FILE *f1, FILE *f2)
{
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
                // break;
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
}

void getSpecialSymbols(char line[], int row, Token token[])
{
    for (int i = 0; i < strlen(line); i++)
    {
        for (int k = 0; k < 14; k++)
        {
            if (SpecialSymbol[k] == line[i])
            {
                strcpy(token[ind].type, "Special Symbol");
                token[ind].name[0] = SpecialSymbol[k];
                token[ind].name[1] = '\0';
                token[ind].row = row;
                token[ind].col = i;
                ind++;
            }
        }
    }
}

int notArithmop(char ch)
{
    if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '%')
        return 1;
    return 0;
}
int notLogical(char ch)
{
    if (ch != '&' && ch != '|' && ch != '!')
        return 1;
    return 0;
}
void getAllOperator(char line[], int row, Token token[])
{
    for (int i = 0; i < strlen(line); i++)
    {
        // Relational Operator
        if (line[i] == '=' && line[i + 1] == '=' || line[i] == '!' && line[i + 1] == '=' || line[i] == '>' && line[i + 1] == '=' || line[i] == '<' && line[i + 1] == '=')
        {
            strcpy(token[ind].type, "Relop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = line[i + 1];
            token[ind].name[2] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }
        if (line[i] == '>' && line[i + 1] != '=' || line[i] == '<' && line[i + 1] != '=')
        {
            strcpy(token[ind].type, "Relop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }

        // Arithmetic Operator
        if (line[i] == '+' && notArithmop(line[i + 1]) && notArithmop(line[i - 1]) || line[i] == '-' && notArithmop(line[i + 1]) && notArithmop(line[i - 1]) || line[i] == '*' && notArithmop(line[i + 1]) && notArithmop(line[i - 1]) || line[i] == '/' && notArithmop(line[i + 1]) && notArithmop(line[i - 1]) || line[i] == '%' && notArithmop(line[i + 1]) && notArithmop(line[i - 1]))
        {
            strcpy(token[ind].type, "Arithop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }

        // Logical Operator
        if (line[i] == '&' && line[i + 1] == '&' || line[i] == '|' && line[i + 1] == '|')
        {
            strcpy(token[ind].type, "Logicalop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = line[i + 1];
            token[ind].name[2] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }

        if (line[i] == '!' && notLogical(line[i + 1]))
        {
            strcpy(token[ind].type, "Logicalop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }

        // Assignment Operator
        if (line[i] == '=' && line[i - 1] != '=' && line[i + 1] != '=')
        {
            strcpy(token[ind].type, "Assignmentop");
            token[ind].name[0] = line[i];
            token[ind].name[1] = '\0';
            token[ind].row = row;
            token[ind].col = i;
            ind++;
        }
    }
}

void getStringLiterals(char line[], int row, Token token[])
{
    char literal[400];
    int j = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '"')
        {
            token[ind].col = i;
            i++;
            while (line[i] != '"')
            {
                literal[j] = line[i];
                j++;
                i++;
            }
        }
        literal[j] = '\0';
    }
    if (strlen(literal) != 0)
    {
        strcpy(token[ind].type, "StringLiteral");
        strcpy(token[ind].name, literal);
        token[ind].row = row;
        ind++;
        strcpy(literal, "");
    }
}

void getNumericLiterals(char line[], int row, Token token[])
{
    char str[344];
    int insideQuotes = 0;
    int j = 0;

    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == '"')
        {
            insideQuotes = !insideQuotes;
            i++;
        }
        if (!insideQuotes && (line[i] >= '0' && line[i] <= '9'))
        {
            token[ind].col = i;
            while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.')
            {
                str[j] = line[i];
                j++;
                i++;
            }
        }
        str[j] = '\0';
    }
    if (strlen(str) != 0)
    {
        strcpy(token[ind].type, "Numeric Literal");
        strcpy(token[ind].name, str);
        token[ind].row = row;
        ind++;
        strcpy(str, "");
    }
}

int isKeyword(char word[])
{
    for (int k = 0; k < 32; k++)
    {
        if (strcmp(keywords[k], word) == 0)
        {
            return 1;
        }
    }
    return 0;
}
void getKeywordsAndIdentifiers(char line[], int row, Token token[])
{
    char word[100];
    char str[100];
    for (int i = 0; i < strlen(line); i++)
    {
        int j = 0;
        int argCount = 0;

        if (line[i] == '"')
        {
            do
            {
                i++;
            } while (line[i] != '"');
        }

        if (line[i] == '\'')
        {
            do
            {
                i++;
            } while (line[i] != '\'');
        }

        if ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || line[i] == '_')
        {
            while ((line[i] >= 'a' && line[i] <= 'z') || (line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= '0' && line[i] <= '9') || line[i] == '_')
            {
                word[j] = line[i];
                j++;
                i++;
            }
            word[j] = '\0';

            if (isKeyword(word))
            {
                strcpy(token[ind].type, "Keyword");
                strcpy(token[ind].name, word);
                token[ind].row = row;
                token[ind].col = i - strlen(word);
                ind++;
            }
            else if (!isKeyword(word))
            {
                identifier_count++;
                sprintf(str, "id-%d", identifier_count);
                strcpy(token[ind].type, "Identifier");
                strcpy(token[ind].name, str);
                token[ind].row = row;
                token[ind].col = i - strlen(word);
                ind++;
            }
        }
    }
}

int main()
{
    FILE *f1, *f2;
    char filename[100], c;

    f1 = fopen("Input.txt", "r");

    if (f1 == NULL)
    {
        printf("cannot open the file\n");
        exit(0);
    }

    f2 = fopen("Output.txt", "w+");

    removepreandcom(f1, f2);
    fclose(f2);

    f2 = fopen("Output.txt", "r");

    int row = 1;
    char line[2222];
    Token token[256];
    while (fgets(line, sizeof(line), f2))
    {
        if (strstr(line, "include") != NULL && strstr(line, "define") != NULL)
        {
            continue;
        }

        getKeywordsAndIdentifiers(line, row, token);
        getSpecialSymbols(line, row, token);
        getAllOperator(line, row, token);
        getStringLiterals(line, row, token);
        getNumericLiterals(line, row, token);
        row++;
    }

    printf("TOKENS:\n\n");
    displayToken(token);

    fclose(f1);
    fclose(f2);
}