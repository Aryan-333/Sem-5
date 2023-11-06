#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TokenGenerator.c"

// jaha token name check hota hai vha lagate hai retract
// flag vha lagate hai jha recursive call hoti hai ya jese stmt_list mei subtitute karke bhi laga sakte hai

FILE *f1, *f2;
Token token;

int decl_flag = 1;
int stmt_flag = 1;
int rel_flag = 1;
int sp_flag = 1;
int mul_flag = 1;

void expression();
void statement_list();
void data_type();
void id_list();
void listPrime();
void SElistPrime();
void statement();
void assignment_stat();
void decision_stat();
void looping_stat();
void dprime();
void simple_expression();
void eprime();
void seprime();
void term();
void relop();
void addop();
void mulop();
void factor();
void tprime();

void retract()
{
    fseek(f2, -strlen(token.token_name), SEEK_CUR);
}

void invalid(char str[])
{
    printf("===========Parse Unsuccessful===============\n");
    printf("Error in function %s\n", str);
    exit(0);
}

void declarations()
{
    data_type();
    id_list();

    token = getNextToken(f2);

    if (decl_flag && strcmp(token.token_name, ";") == 0)
    {
        declarations();
    }
    else
    {
        retract();
    }
}

void data_type()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, "int") == 0 || strcmp(token.token_name, "char") == 0)
    {
        decl_flag = 1;
        return;
    }
    else
    {
        retract();
        decl_flag = 0;
    }
}

void id_list()
{
    if (decl_flag)
    {
        token = getNextToken(f2);
        if (strcmp(token.type, "id") == 0)
        {
            listPrime();
        }
    }
}

void listPrime()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, ",") == 0)
    {
        id_list();
    }
    else if (strcmp(token.token_name, "[") == 0)
    {
        token = getNextToken(f2);

        if (strcmp(token.type, "Numeric Literal") == 0)
        {
            token = getNextToken(f2);
            if (strcmp(token.token_name, "]") == 0)
            {
                SElistPrime();
            }
            else
            {
                invalid("listPrime 1");
            }
        }
        else
        {
            invalid("listPrime 2");
        }
    }
    else
    {
        retract();
    }
}

void SElistPrime()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, ",") == 0)
    {
        id_list();
    }
    else
    {
        retract();
    }
}

void statement_list()
{
    token = getNextToken(f2);

    if (strcmp(token.type, "id") == 0 || strcmp(token.token_name, "if") == 0 || strcmp(token.token_name, "for") == 0 || strcmp(token.token_name, "while") == 0)
    {
        retract();

        statement();
        if (stmt_flag)
        {
            statement_list();
        }
    }

    else
    {
        retract();
        return;
    }
}

void statement()
{
    token = getNextToken(f2);
    if (strcmp(token.type, "id") == 0)
    {
        stmt_flag = 1;
        retract();

        assignment_stat();

        token = getNextToken(f2);

        if (strcmp(token.token_name, ";") == 0)
            return;
        else
            retract();
    }
    else if (strcmp(token.token_name, "if") == 0)
    {
        stmt_flag = 1;
        retract();

        decision_stat();
    }
    else if (strcmp(token.token_name, "for") == 0 || strcmp(token.token_name, "while") == 0)
    {
        stmt_flag = 1;
        retract();

        looping_stat();
    }
    else
    {
        stmt_flag = 0;
        retract();
    }
}

void assignment_stat()
{
    token = getNextToken(f2);

    if (strcmp(token.type, "id") == 0)
    {
        token = getNextToken(f2);

        if (strcmp(token.token_name, "=") == 0)
        {
            expression();
        }
        else
            invalid("assignment");
    }
    else
    {
        retract();
    }
}

void decision_stat()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "if") == 0)
    {
        token = getNextToken(f2);
        if (strcmp(token.token_name, "(") == 0)
        {
            expression();
            token = getNextToken(f2);

            if (strcmp(token.token_name, ")") == 0)
            {
                token = getNextToken(f2);
                if (strcmp(token.token_name, "{") == 0)
                {
                    statement_list();
                    token = getNextToken(f2);
                    if (strcmp(token.token_name, "}") == 0)
                    {
                        dprime();
                    }
                    else
                        invalid("decision }");
                }
                else
                    invalid("decision {");
            }
            else
                invalid("decision )");
        }
        else
            invalid("decision (");
    }
}

void looping_stat()
{
    // printf("for loop 0\n");
    token = getNextToken(f2);

    if (strstr(token.token_name, "for") != NULL)
    {
        token = getNextToken(f2);
        // printf("for loop 1");
        if (strcmp(token.token_name, "(") == 0)
        {
            assignment_stat();
            token = getNextToken(f2);
            // printf("for loop 2");

            if (strcmp(token.token_name, ";") == 0)
            {
                expression();
                token = getNextToken(f2);
                // printf("for loop 3");

                if (strcmp(token.token_name, ";") == 0)
                {
                    assignment_stat();
                    token = getNextToken(f2);
                    // printf("for loop 4");

                    if (strcmp(token.token_name, ")") == 0)
                    {
                        token = getNextToken(f2);
                        // printf("for loop 5");

                        if (strcmp(token.token_name, "{") == 0)
                        {
                            statement_list();
                            token = getNextToken(f2);
                            // printf("for loop 6");

                            if (strcmp(token.token_name, "}") == 0)
                            {
                                printf("for loop success");
                                return;
                            }
                            else
                                invalid(" loop }");
                        }
                        else
                            invalid("loop {");
                    }
                    else
                        invalid("loop )");
                }
                else
                    invalid("loop (");
            }
            else
                invalid("loop (");
        }
        else
            invalid("loop (");
    }

    else if (strcmp(token.token_name, "while") == 0)
    {
        token = getNextToken(f2);

        if (strcmp(token.token_name, "(") == 0)
        {
            expression();
            token = getNextToken(f2);
            if (strcmp(token.token_name, ")") == 0)
            {
                token = getNextToken(f2);
                if (strcmp(token.token_name, "{") == 0)
                {
                    statement_list();
                    token = getNextToken(f2);
                    if (strcmp(token.token_name, "}") == 0)
                    {
                        printf("while loop success");
                        return;
                    }
                    else
                        invalid(" loop }");
                }
                else
                    invalid("loop {");
            }
            else
                invalid("loop )");
        }
        else
            invalid("loop (");
    }
    else
    {
        invalid("looooooppppp");
    }
}

void dprime()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, "else") == 0)
    {
        token = getNextToken(f2);
        if (strcmp(token.token_name, "{") == 0)
        {
            statement_list();
            if (strcmp(token.token_name, "}") == 0)
            {
                printf("decision successful");
                return;
            }
            else
                invalid("}");
        }
        else
            invalid("{");
    }
    else
    {
        retract();
    }
}

void expression()
{
    simple_expression();
    eprime();
}

void simple_expression()
{
    term();
    seprime();
}

void eprime()
{
    relop();
    if (rel_flag)
    {
        simple_expression();
    }
}

void seprime()
{
    addop();
    if (sp_flag)
    {
        term();
        seprime();
    }
}

void term()
{
    factor();
    tprime();
}

void tprime()
{
    mulop();
    if (mul_flag)
    {
        factor();
        tprime();
    }
}

void factor()
{
    token = getNextToken(f2);

    if (strcmp(token.type, "id") == 0 || strcmp(token.type, "Numeric Literal") == 0)
    {
        return;
    }
    else
    {
        retract();
    }
}

void relop()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, "==") == 0 || strcmp(token.token_name, "!=") == 0 || strcmp(token.token_name, ">=") == 0 || strcmp(token.token_name, "<=") == 0 || strcmp(token.token_name, ">") == 0 || strcmp(token.token_name, "<") == 0)
    {
        rel_flag = 1;
        return;
    }
    else
    {
        rel_flag = 0;
        retract();
    }
}

void addop()
{
    token = getNextToken(f2);
    if (strcmp(token.token_name, "+") == 0 || strcmp(token.token_name, "-") == 0)
    {
        sp_flag = 1;
        return;
    }
    else
    {
        retract();
        sp_flag = 0;
    }
}

void mulop()
{
    token = getNextToken(f2);

    if (strcmp(token.token_name, "*") == 0 || strcmp(token.token_name, "/") == 0 || strcmp(token.token_name, "%") == 0)
    {
        mul_flag = 1;
        return;
    }
    else
    {
        retract();
        mul_flag = 0;
    }
}

void program()
{
    token = getNextToken(f2);

    token = getNextToken(f2);

    if (strcmp(token.token_name, "main") == 0)
    {
        token = getNextToken(f2);
        if (strcmp(token.token_name, "(") == 0)
        {
            token = getNextToken(f2);
            if (strcmp(token.token_name, ")") == 0)
            {
                token = getNextToken(f2);
                if (strcmp(token.token_name, "{") == 0)
                {
                    declarations();
                    statement_list();
                    token = getNextToken(f2);

                    if (strcmp(token.token_name, "}") == 0)
                    {
                        printf("Parse Successful");
                    }
                    else
                    {
                        invalid("program1");
                        printf("Missing parentheses }\n");
                    }
                }
                else
                {

                    invalid("program2");
                    printf("Missing parentheses {\n");
                }
            }
            else
            {

                invalid("program3");
                printf("Missing parentheses )\n");
            }
        }
        else
        {

            invalid("program4");
            printf("Missing parentheses (\n");
        }
    }
    else
        invalid("program5");
}

int main()
{
    char filename[100];
    // printf("Enter file name");
    // gets(filename);

    f1 = fopen("input.c", "r");
    f2 = fopen("output.txt", "w+");

    removePreandComment(f1, f2);
    fclose(f2);

    f2 = fopen("output.txt", "r");

    program();
}