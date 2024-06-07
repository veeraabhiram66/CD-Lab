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

int isKeyword(const char *token) {
    int numKeywords = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < numKeywords; ++i) {
        if (strcmp(token, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int isOperator(const char *token) {
    if (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '%' || token[0] == '=') {
        return 1;
    }
    return 0;
}

int isPunctuator(const char *token) {
    if (token[0] == '(' || token[0] == ')' || token[0] == '{' || token[0] == '}' || token[0] == '[' || token[0] == ']' || token[0] == ';' || token[0] == ',' || token[0] == '.') {
        return 1;
    }
    return 0;
}

int isStringLiteral(const char *token) {
    if (token[0] == '"') {
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
    int tokenkeyword = 0, tokenstring = 0, tokenidentifier = 0, tokenopearator = 0, tokencons = 0, tokenspecial = 0;
    char buffer[MAX_TOKEN_LENGTH];
    enum TokenType tokenType;

    while (fscanf(file, "%s", buffer) != EOF) {
        tokenType = KEYWORD;
        if (isKeyword(buffer))
        {
            ++tokenkeyword;
        } 
        else if (isOperator(buffer)) 
        {
            ++tokenopearator;
        } 
        else if (isPunctuator(buffer)) 
        {
            ++tokenspecial;
        } 
        else if (isStringLiteral(buffer)) 
        {
            ++tokenstring;
        } 
        else if (isConstant(buffer)) 
        {
            ++tokencons;
        } 
        else if (isIdentifier(buffer)) 
        {
            ++tokenidentifier;
        }
    }
    printf("Total tokens: %d\n", tokenkeyword + tokenstring + tokenidentifier + tokenopearator + tokenspecial + tokencons);
    printf("Total keywords: %d\n", tokenkeyword);
    printf("Total string literals: %d\n", tokenstring);
    printf("Total identifiers: %d\n", tokenidentifier);
    printf("Total operators: %d\n", tokenopearator);
    printf("Total special characters: %d\n", tokenspecial);
    printf("Total constants: %d\n", tokencons);
    fclose(file);
    return 0;
}