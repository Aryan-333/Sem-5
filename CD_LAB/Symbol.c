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

typedef struct
{
    int index;
    char symbolName[100];
    char returnType[100];
    char type[100];
    char args[10];
} Symbol;

typedef struct node
{
    Symbol data;
    struct node *next;
} TableElement;

TableElement *list = NULL;
Symbol symbol;

const char *keywords[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum",
                          "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static",
                          "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};

char SpecialSymbol[] = {'$', '[', ']', '{', '}', '(', ')', '.', ',', ':', ';', '?', '"', '\\'};

void DisplayTable(TableElement **list)
{
    printf("SYMBOL TABLE\n\n\n");
    printf("Index \t Symbol Name \t Type \t Return Type \t No. of Arguments\t\n");
    TableElement *temp = *list;
    while (temp != NULL)
    {
        printf("%d \t %s \t %s \t %s\t %s\n", temp->data.index, temp->data.symbolName, temp->data.type, temp->data.returnType, temp->data.args);
        temp = temp->next;
    }
}

int Search(char str[], TableElement **list)
{
    TableElement *temp = *list;

    if (temp == NULL)
    {
        return 0;
    }

    while (temp != NULL)
    {
        if (strcmp(temp->data.symbolName, str) == 0)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

TableElement *insert(Symbol symbol, TableElement *list)
{
    TableElement *newNode = (TableElement *)malloc(sizeof(TableElement));

    newNode->data = symbol;
    newNode->next = NULL;

    if (list == NULL)
    {
        list = newNode;
        return list;
    }

    TableElement *temp = list;

    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
    return list;
}

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
            else if (line[i] == '/' && line[i + 1] == '*' && !insideQuote)
            {
                do
                {
                    i++;
                    if (line[i + 1] == '\n')
                    {
                        mlc_flag = 1;
                        break;
                    }
                } while (line[i + 1] != '*' && line[i + 2] != '/');
                break;
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
                else
                {
                    fputc(line[i], f2);
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
                if (Search(word, &list) == 0)
                {
                    identifier_count++;
                    sprintf(str, "id-%d", identifier_count);
                    strcpy(token[ind].type, "Identifier");
                    strcpy(token[ind].name, word);
                    token[ind].row = row;
                    token[ind].col = i - strlen(word);

                    int temp_i = i;
                    symbol.index = identifier_count;
                    strcpy(symbol.symbolName, word);

                    if (line[i] == '(')
                    {
                        strcpy(symbol.type, "FUNC");
                        if ((strcmp(word, "printf") == 0) || (strcmp(word, "scanf") == 0))
                        {
                            strcpy(symbol.returnType, "int");
                            sprintf(symbol.args, "%d", 1);
                        }
                        else
                        {
                            if (line[i + 1] == ')')
                            {
                                sprintf(symbol.args, "%d", 0);
                            }
                            else
                            {
                                do
                                {
                                    temp_i++;
                                    if (line[i] == ',')
                                        argCount++;

                                } while (line[temp_i] != ')');
                                sprintf(symbol.args, "%d", argCount + 1);
                            }
                            strcpy(symbol.returnType, token[ind - 1].name);
                        }
                    }
                    else
                    {
                        strcpy(symbol.type, token[ind - 1].name);
                        strcpy(symbol.returnType, "--");
                        sprintf(symbol.args, "%d", 0);
                    }
                    list = insert(symbol, list);
                }
                ind++;
            }
            strcpy(word, "");
            j = 0;
        }
    }
}

int main()
{
    FILE *f1, *f2;
    char filename[100], c;

    f1 = fopen("sinput.txt", "r");

    if (f1 == NULL)
    {
        printf("cannot open the file\n");
        exit(0);
    }

    f2 = fopen("soutput.txt", "w+");

    removepreandcom(f1, f2);
    fclose(f2);

    f2 = fopen("soutput.txt", "r");

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

    DisplayTable(&list);

    fclose(f1);
    fclose(f2);
}