//by using transition states
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
//use transition state to detect the token type
enum TokenType detectTokenType(const char *token) {
    enum TokenType tokenType = KEYWORD;
    int state = 0;
    int i = 0;
    while (token[i] != '\0') {
        switch (state) {
            case 0:
                if (isalpha(token[i])) {
                    state = 1;
                } else if (isdigit(token[i])) {
                    state = 2;
                } else if (token[i] == '"') {
                    state = 3;
                } else if (token[i] == '+' || token[i] == '-' || token[i] == '*' || token[i] == '/' || token[i] == '%' || token[i] == '=') {
                    state = 4;
                } else if (token[i] == '(' || token[i] == ')' || token[i] == '{' || token[i] == '}' || token[i] == '[' || token[i] == ']' || token[i] == ';' || token[i] == ',' || token[i] == '.') {
                    state = 5;
                } else {
                    state = 6;
                }
                break;
            case 1:
                if (isalpha(token[i]) || isdigit(token[i])) {
                    state = 1;
                } else {
                    state = 6;
                }
                break;
            case 2:
                if (isdigit(token[i])) {
                    state = 2;
                } else {
                    state = 6;
                }
                break;
            case 3:
                if (token[i] == '"') {
                    state = 6;
                } else {
                    state = 3;
                }
                break;
            case 4:
                state = 6;
                break;
            case 5:
                state = 6;
                break;
            case 6:
                break;
        }
        ++i;
    }
    switch (state) {
        case 1:
            tokenType = IDENTIFIER;
            break;
        case 2:
            tokenType = CONSTANT;
            break;
        case 3:
            tokenType = STRING_LITERAL;
            break;
        case 4:
            tokenType = OPERATOR;
            break;
        case 5:
            tokenType = PUNCTUATOR;
            break;
        case 6:
            tokenType = KEYWORD;
            break;
    }
    return tokenType;
}
int main(){
    FILE *file = fopen("input.c", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }
    int tokenkeyword = 0, tokenstring = 0, tokenidentifier = 0, tokenopearator = 0, tokencons = 0, tokenspecial = 0;
    char buffer[MAX_TOKEN_LENGTH];
    enum TokenType tokenType;

    while (fscanf(file, "%s", buffer) != EOF) {
        if (buffer[0] == '\0') {
            continue;
        }
        tokenType = detectTokenType(buffer);
        switch (tokenType) {
            case KEYWORD:
                ++tokenkeyword;
                break;
            case IDENTIFIER:
                ++tokenidentifier;
                break;
            case OPERATOR:
                ++tokenopearator;
                break;
            case CONSTANT:
                ++tokencons;
                break;
            case STRING_LITERAL:
                ++tokenstring;
                break;
            case PUNCTUATOR:
                ++tokenspecial;
                break;
        }
    }
    printf("Keywords: %d\n", tokenkeyword);
    printf("Identifiers: %d\n", tokenidentifier);
    printf("Operators: %d\n", tokenopearator);
    printf("Constants: %d\n", tokencons);
    printf("String Literals: %d\n", tokenstring);
    printf("Punctuators: %d\n", tokenspecial);
    printf("Total tokens: %d\n", tokenkeyword + tokenstring + tokenidentifier + tokenopearator + tokenspecial + tokencons);
    return 0;
}