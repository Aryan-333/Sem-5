#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char token_name[200];
    char type[100];
} Token;

const char *keyword[] = {"auto", "break", "case", "char", "continue", "do", "default", "const", "double", "else", "enum",
                         "extern", "for", "if", "goto", "float", "int", "long", "register", "return", "signed", "static",
                         "sizeof", "short", "struct", "switch", "typedef", "union", "void", "while", "volatile", "unsigned"};

FILE *f1, *f2;
Token token;
int func_flag = 0;

void displayToken(Token token)
{
    printf("<%s ,  %s>\n", token.token_name, token.type);
}

void removePreandComment(FILE *f1, FILE *f2)
{

    int insideQuote = 0;
    char ch = fgetc(f1);

    while (ch != EOF)
    {
        if (ch == '"')
        {
            insideQuote = !insideQuote;
            fputc(ch, f2);
            ch = fgetc(f1);
        }
        if (ch == '/' && !insideQuote)
        {
            ch = fgetc(f1);
            if (ch == '/')
            {
                do
                {
                    ch = fgetc(f1);
                } while (ch != '\n');
            }
            else if (ch == '*')
            {

                do
                {
                    while (ch != '*')
                    {
                        ch = fgetc(f1);
                    }
                    ch = fgetc(f1);
                } while (ch != '/');
                ch = fgetc(f1);
            }
            else
            {
                fseek(f1, -2, SEEK_CUR);
                ch = fgetc(f1);
            }
        }
        if (ch == '#' && !insideQuote && func_flag == 0)
        {
            do
            {
                ch = fgetc(f1);
            } while (ch != '\n');
        }
        else
        {
            if (ch == '{')
            {
                func_flag++;
            }
            else if (ch == '}')
            {
                func_flag--;
            }
            fputc(ch, f2);
            ch = fgetc(f1);
        }
    }
}

int isKeyword(char str[])
{
    for (int k = 0; k < 32; k++)
    {
        if (strcmp(keyword[k], str) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isSpecial(char ch)
{
    if (ch == '\'' || ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == '$' || ch == '[' || ch == ']' || ch == '.' || ch == ',' || ch == ':' || ch == ';')
        return 1;
    return 0;
}

int NotARelop(char ch)
{
    if (ch != '>' && ch != '<' && ch != '=' && ch != '!')
        return 1;
    return 0;
}

int NotaArithmOp(char ch)
{
    if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '%')
        return 1;
    return 0;
}
int NotALogOp(char ch)
{
    if (ch != '&' && ch != '|' && ch != '!')
        return 1;
    return 0;
}

Token getAllOperator(FILE *f)
{
    fseek(f, -1, SEEK_CUR);
    char ch1 = fgetc(f);
    char ch2 = fgetc(f);

    if (ch1 == '!' && ch1 == '=')
    {
        strcpy(token.token_name, "!=");
        strcpy(token.type, "NE");
    }
    else if (ch1 == '<' && ch2 == '=')
    {
        strcpy(token.type, "LE");
        strcpy(token.token_name, "<=");
    }
    else if (ch1 == '<' && NotARelop(ch2))
    {
        strcpy(token.type, "LT");
        strcpy(token.token_name, "<");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '=' && ch2 == '=')
    {
        strcpy(token.type, "EQ");
        strcpy(token.token_name, "==");
    }
    else if (ch1 == '>' && ch2 == '=')
    {
        strcpy(token.type, "GE");
        strcpy(token.token_name, ">=");
    }
    else if (ch1 == '>' && NotARelop(ch2))
    {
        strcpy(token.type, "GT");
        strcpy(token.token_name, ">");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '=' && NotARelop(ch2))
    {
        strcpy(token.type, "Assignment");
        strcpy(token.token_name, "=");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '+' && NotaArithmOp(ch2))
    {
        strcpy(token.type, "ADD");
        strcpy(token.token_name, "+");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '-' && NotaArithmOp(ch2))
    {
        strcpy(token.type, "SUB");
        strcpy(token.token_name, "-");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '/' && NotaArithmOp(ch2))
    {
        strcpy(token.type, "DIV");
        strcpy(token.token_name, "/");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '*' && NotaArithmOp(ch2))
    {
        strcpy(token.type, "MUL");
        strcpy(token.token_name, "*");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '%' && NotaArithmOp(ch2))
    {
        strcpy(token.type, "MOD");
        strcpy(token.token_name, "%");
        fseek(f, -1, SEEK_CUR);
    }
    else if (ch1 == '&' && ch2 == '&')
    {
        strcpy(token.type, "Logical AND");
        strcpy(token.token_name, "&&");
    }
    else if (ch1 == '|' && ch2 == '|')
    {
        strcpy(token.type, "Logical OR");
        strcpy(token.token_name, "||");
    }
    else if (ch1 == '!' && NotALogOp(ch2))
    {
        strcpy(token.type, "Logical NOT");
        strcpy(token.token_name, "!");
        fseek(f, -1, SEEK_CUR);
    }

    return token;
}

Token getKeywordAndIdentifier(FILE *f)
{
    fseek(f, -1, SEEK_CUR);
    char ch = fgetc(f);

    char word[100];
    int j = 0;

    while (isalpha(ch) || ch == '_')
    {
        word[j++] = ch;
        ch = fgetc(f);
    }
    fseek(f, -1, SEEK_CUR);
    word[j] = '\0';

    if (isKeyword(word))
    {
        strcpy(token.type, "KW");
        strcpy(token.token_name, word);
    }
    else if (!isKeyword(word))
    {
        strcpy(token.token_name, word);
        strcpy(token.type, "id");
    }
    strcpy(word, "");
    j = 0;

    return token;
}

Token getStringLiteral(FILE *f)
{
    char str[100];
    char ch = fgetc(f);
    int j = 0;
    while (ch != '"')
    {
        str[j++] = ch;
        ch = fgetc(f);
    }
    str[j] = '\0';

    if (strlen(str) != 0)
    {
        strcpy(token.token_name, str);
        strcpy(token.type, "String Literal");
        strcpy(str, "");
    }
    return token;
}

Token getCharacterLiteral(FILE *f)
{
    char str[100];
    char ch = fgetc(f);
    int j = 0;
    while (ch != '\'')
    {
        str[j++] = ch;
        ch = fgetc(f);
    }
    str[j] = '\0';

    if (strlen(str) != 0)
    {
        strcpy(token.token_name, str);
        strcpy(token.type, "Character Literal");
        strcpy(str, "");
    }
    return token;
}

Token getNumericLiteral(FILE *f)
{
    char str[100];
    fseek(f, -1, SEEK_CUR);
    char ch = fgetc(f);

    int j = 0;
    while (isdigit(ch) || ch == '.')
    {
        str[j++] = ch;
        ch = fgetc(f);
    }
    fseek(f, -1, SEEK_CUR); ///////////////////////////////
    str[j] = '\0';

    if (strlen(str) != 0)
    {
        strcpy(token.token_name, str);
        strcpy(token.type, "Numeric Literal");
        strcpy(str, "");
    }
    return token;
}

Token getNextToken(FILE *f)
{
    char ch = fgetc(f);

    while (isspace(ch))
    {
        ch = fgetc(f);
    }

    while (ch == '#')
    {
        printf("%c", ch);
        do
        {
            ch = fgetc(f);
        } while (ch != '\n');

        ch = fgetc(f);
    }

    if (ch == EOF)
    {
        exit(0);
    }

    if (ch == '"')
    {
        return getStringLiteral(f);
    }
    else if (ch == '\'')
        return getCharacterLiteral(f);
    else if (isalpha(ch) || ch == '_')
        return getKeywordAndIdentifier(f);
    else if (isdigit(ch))
        return getNumericLiteral(f);
    else if (isSpecial(ch))
    {
        strcpy(token.type, "Special Symbol");
        token.token_name[0] = ch;   // Assign the character directly
        token.token_name[1] = '\0'; // Null-terminate the string

        return token;
    }
    else
    {
        return getAllOperator(f);
    }
}

// int main()
// {
//     char filename[100];
//     // printf("Enter file name");
//     // gets(filename);

//     f1 = fopen("input.c", "r");
//     f2 = fopen("output.txt", "w+");

//     removePreandComment(f1, f2);
//     fclose(f2);

//     f2 = fopen("output.txt", "r");

//     while (!feof(f2))
//     {
//         token = getNextToken(f2); // Get the next token
//         displayToken(token);      // Display the token
//     }
// }