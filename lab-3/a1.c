//Given a file name, Write a C program to take it as an argument to count the number of tokens and detect the type of tokens
//Removing preprocessor directives, whitespaces, tab spaces, empty lines, and comments lines.
//Identify the tokens and detect the tokens with their 6 types
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100

enum TokenType {
    KEYWORD,
    IDENTIFIER,
    OPERATOR,
    CONSTANT,
    STRING_LITERAL,
    PUNCTUATOR
};

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof", "static",
    "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

//take string and divide it into tokens
/*
char *tokenize(char *str, char *delim)
{
    static char *input = NULL;
    if (str != NULL)
    {
        input = str;
    }
    if (input == NULL)
    {
        return NULL;
    }
    char *token = malloc(sizeof(char) * 100);
    int i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ' ' || input[i] == '\n' || input[i] == '\t')
        {
            token[i] = '\0';
            input = input + i + 1;
            return token;
        }
        token[i] = input[i];
        i++;
    }
    token[i] = '\0';
    input = NULL;
    return token;
}
*/
//token is the return value of the tokenize function
int isKeyword(const char *token) {
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

//breaking the code into tokens
int isOperator(const char *token) {
    for(int i = 0; token[i] != '\0'; ++i) {
        if (token[i] == '+' || token[i] == '-' || token[i] == '*' || token[i] == '/' || token[i] == '%' || token[i] == '=') {
            return 1;
        }
    }
    return 0;
}

int isPunctuator(const char *token) {
    for(int i = 0; token[i] != '\0'; ++i) {
        if (token[i] == '(' || token[i] == ')' || token[i] == '{' || token[i] == '}' || token[i] == '[' || token[i] == ']' || token[i] == ';' || token[i] == ',' || token[i] == '.') {
            return 1;
        }
    }
    return 0;
}

int isStringLiteral(const char *token) {
    if (token[0] == '"')
     {
        return 1;
    }
    return 0;
}

int isConstant(const char *token) {
    int i = 0;
    while (token[i] != '\0') {
        if (!isdigit(token[i])) {
            return 0;
        }
        ++i;
    }
    return 1;
}

int isIdentifier(const char *token) {
    int i = 0;
    while (token[i] != '\0') {
        if (!isalpha(token[i])) {
            return 0;
        }
        ++i;
    }
    return 1;
}

int main() {

    FILE *file = fopen("ca.c", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    int tokenkeyword = 0, tokenstring = 0, tokenidentifier = 0, tokenopearator = 0, tokencons = 0, tokenpunctuator = 0;
    char buffer[MAX_TOKEN_LENGTH];
    //string is the input file words by dividing with space
  //  char * str=fgets(file,buffer,MAX_TOKEN_LENGTH);
   // char *delim=" ";
    //char * token=tokenize(str,delim);
    enum TokenType tokenType;

    while (fscanf(file, "%s", buffer) != EOF) {
        if (buffer[0] == '\0') {
            continue;
        }

        if(isKeyword(buffer)){
            tokenType = KEYWORD;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokenkeyword++;
        }

        else if(isalpha(buffer[0])){
            tokenType = IDENTIFIER;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokenidentifier++;
        }

        else if(isdigit(buffer[0])){
            tokenType = CONSTANT;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokencons++;
        }

        else if(buffer[0] == '"'){
            tokenType = STRING_LITERAL;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokenstring++;
        }

        else if(isPunctuator(buffer))
        {
            tokenType = PUNCTUATOR;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokenpunctuator++;
        }

        else if(isOperator(buffer))
        {
            tokenType = OPERATOR;
            printf("Token: %s\tType: %d\n", buffer, tokenType);
            tokenopearator++;
        }
        else{
            printf("Token: %s\tType: %d\n", buffer, tokenType);
        }
    }
    printf("Total tokens: %d\n", tokenkeyword + tokenstring + tokenidentifier + tokenopearator + tokenpunctuator + tokencons);
    printf("Total keywords: %d\n", tokenkeyword);
    printf("Total string literals: %d\n", tokenstring);
    printf("Total identifiers: %d\n", tokenidentifier);
    printf("Total operators: %d\n", tokenopearator);
    printf("Total special characters: %d\n", tokenpunctuator);
    printf("Total constants: %d\n", tokencons);
    fclose(file);
    return 0;
}









