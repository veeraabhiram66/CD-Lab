/*
Roll: CS21B2026
Name: P.Veera Abhiram
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LINE_LENGTH 100

int isKeyword(char *str){
    char keywords[][10] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do", "double", 
        "else", "enum", "extern", "float", "for", "goto", "if", "int", "long", "register", 
        "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", 
        "union", "unsigned", "void", "volatile", "while"};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }}
    return(0);
}

int isIdentifier(char *str){
    int tokensize = strlen(str);
    for(int i=0; i<tokensize; i++){
        if(i==0){
            if(!isalpha(str[i])){
                return(0);}
        }
        else{
            if(!isalpha(str[i])&&!isdigit(str[i])){
                return(0);}
        }
    }
    return(1);
}


int isInteger(char *str){
    char quali[] = "uUlL";
    int tokensize = strlen(str);
    for(int i=0; i<tokensize; i++){
        if(i==0){
            if(!isdigit(str[i])){
                return(0);}
        }
        else{
            if(!isdigit(str[i]) && !strchr(quali, str[i])){
                return(0);}
        }
    }
    return(1);
}

int isHexOrOcta(char *str){
    int tokensize = strlen(str);
    int state;
    char dighex[] = "0123456789ABCDEF";
    char digoct[] = "01234567";
    char quali[] = "uUlL";
    
    for(int i=0; i<tokensize; i++){
        if(i==0){
            if(str[i] != '0'){
                return(0);}
        }
        else{
            if(i==1){
                if(str[i] == 'x' || str[i] == 'X'){
                    state = 1;}
                else if(strchr(digoct, str[i])){
                    state = 2;}
                else{
                    return(0);}
            }
            else{
                if(state == 1){
                    if(i==2){
                        if(!strchr(dighex, str[i])){
                            return(0);}
                    }
                    else{
                        if(!strchr(dighex, str[i]) && !strchr(quali, str[i])){
                            return(0);}
                    }
                }
                else{
                    if(!strchr(digoct, str[i]) && !strchr(quali, str[i])){
                            return(0);}
                }
            }
        }
    }
    return(1);
}

int isReal(char *str){
    int tokensize = strlen(str);
    int state = 0;
    char quali[] = "fFlL";

    for(int i=0; i<tokensize; i++){
        switch (state)
        {
        case 0: 
            if(isdigit(str[i])){
                state = 2;}
            else if(str[i]=='.'){
                state  = 1;}
            else{
                state = 4;}
            break;

        case 1:
            if(isdigit(str[i])){
                state = 3;}
            else{
                state = 4;}
            break;

        case 2:
            if(isdigit(str[i])){
                state = 2;}
            else if(str[i] == '.'){
                state = 3;}
            else if(str[i] == 'E' || str[i] == 'e'){
                state = 5;}
            else{
                state = 4;}
            break;
        case 3:
            if(isdigit(str[i])){
                state = 3;}
            else if(str[i] == 'E' || str[i] == 'e'){
                state = 5;}
            else{
                state = 4;}
            break;
        case 4:
            return(0);
        case 5:
            if(str[i] == '+' || str[i] == '-'){
                state = 6;}
            else if(isdigit(str[i])){
                state = 7;}
            else{
                state = 8;}
            break;
        case 6:
            if(isdigit(str[i])){
                state = 7;}
            else{
                state = 8;}
            break;
        case 7:
            if(isdigit(str[i])){
                state = 7;}
            else if(strchr(quali, str[i])){
                state = 9;}
            else{
                state = 8;}
        case 8:
            return(0);
        case 9:
            if(str[i]){
                return(0);}
            break;
        default:
            break;
        }
        if (state == 4 || state == 8){
            return(0);
        }
    }
    return(1);
}

int isOperator(char *str) {
    int tokensize = strlen(str);
    int state = 0;
    for(int i=0; i<tokensize; i++){
        switch (state){
        case 0: 
            if(str[i] == '+'){
                state = 1;}
            else if(str[i] == '-'){
                state = 2;}
            else if(str[i] == '*' || str[i] == '/' || str[i] == '%' || str[i] == '='){
                state = 3;}
            else if(str[i] == '<'){
                state = 4;}
            else if(str[i] == '>'){
                state = 5;}
            else if(str[i] == '&'){
                state = 6;}
            else if(str[i] == '|'){
                state = 7;}
            else if(str[i] == '!'){
                state = 8;}
            else if(str[i] == '^' || str[i] == '~'){
                state = 9;}
            else{
                state = 11;}
            break;
        case 1:
            if(str[i] == '+'){
                state = 10;}
            else if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 2:
            if(str[i] == '-'){
                state = 10;}
            else if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 3:
            if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 4:
            if(str[i] == '<'){
                state = 10;}
            else if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 5:
            if(str[i] == '>'){
                state = 10;}
            else if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 6:
            if(str[i] == '&'){
                state = 10;}
            else{
                state = 11;}
            break;
        case 7:
            if(str[i] == '|'){
                state = 10;}
            else{
                state = 11;}
            break;
        case 8:
            if(str[i] == '='){
                state = 10;}
            else{
                state = 11;}
            break;
        case 9:
            if(str[i]){
                state = 11;}
            break;
        case 10:
            if(str[i]){
                state = 11;}
            break;
        case 11:
            return(0);
        default:
            break;
        }
        if(state == 11){
            return(0);
        }
    }
        return(1);
}

void remove_direc(char *line){
    char hash[] = "#";
    char *direc = strstr(line, hash);
    if(direc){
        *direc = '\0';
    }
}

void remove_com(char *line){
    char slash[] = "//";
    char *commentStart = strstr(line, slash);
    if(commentStart){
        *commentStart = '\0';
    }
}

int isDelimiter(char str, int num){
    char *delim = " ,;(){}[]";
    char *delim_b = " ,;(){}[]+-*/%=<>&|!^~";
    if(num == 1){
        if(strchr(delim_b, str)){
            return(1);}
        return(0);
    }
    else{
        if(strchr(delim, str)){
            return(1);}
    }
    return(0);
}

int main(){

    FILE *inputfile = fopen("input.c", "r");
    FILE *outputfile = fopen("details.txt", "w");
    if(!inputfile){
        printf("Error opening input file\n");
        exit(0);
    }
    if(!outputfile){
        printf("Error opening output file\n");
        exit(0);
    }
    char line[MAX_LINE_LENGTH];
    int tokencount = 0, keywords = 0, identifiers = 0, constants = 0, operators = 0, specialchar = 0, strings = 0, invalids = 0, state;

    while(fgets(line, MAX_LINE_LENGTH, inputfile)){
        remove_direc(line);
        remove_com(line);
        char word[100];
        int i = 0;
        int j = 0;
        while(i < strlen(line)){
            if(line[i] == '/' && line[i+1] == '*'){
                state = 10;
            }
            if(state == 10){
                if(line[i] == '*' && line[i+1] == '/'){
                    state = 0;
                    i += 2;}
                else{
                    i++;}
            }
            else{
                if(isspace(line[i])){   
                state = 0;}
            else if(line[i] == '"'){    
                state = 1;}
            else if(isDelimiter(line[i], 0)){  
                state = 2;}
            else if(isalpha(line[i])){
                state = 3;}
            else if(isdigit(line[i])){
                state = 4;}
            else   
            {
                state = 5;}
            switch (state){
                case 0:
                    i++;
                    break;
                case 1: 
                    fprintf(outputfile, "%d.Token : ", tokencount+1);
                    i++;
                    while(line[i] != '"'){
                        printf("%c", line[i]);
                        i++;}
                    fprintf(outputfile, "\t\tType : String\n");
                    i++;
                    strings++;
                    tokencount++;
                    break;
                case 2: 
                    fprintf(outputfile, "%d.Token : %c\t\tType : Special Character\n",tokencount+1, line[i]);
                    i++;
                    specialchar++;
                    tokencount++;
                    break;
                case 3: 
                    fprintf(outputfile, "%d.Token : ", tokencount+1);
                    j = 0;
                    while(!isDelimiter(line[i], 1)){
                        word[j++] = line[i++];
                    }
                    word[j] = '\0';
                    if(isKeyword(word)){
                        fprintf(outputfile, "%s\t\tType : Keyword\n", word);
                        keywords++;
                    }
                    else if(isIdentifier(word)){
                        fprintf(outputfile, "%s\t\tType : Identifier\n", word);
                        identifiers++;
                    }
                    else{
                        fprintf(outputfile, "%s\t\tType : Invalid\n", word);
                        invalids++;
                    }
                    tokencount++;
                    break;
                case 4: 
                    fprintf(outputfile, "%d.Token : ", tokencount+1);
                    j = 0;
                    while(!isDelimiter(line[i], 1)){
                        word[j] = line[i];
                        j++;
                        i++;}
                    word[j] = '\0';
                    if(isInteger(word) || isHexOrOcta(word) || isReal(word)){
                        fprintf(outputfile, "%s\t\tType : Constant\n", word);
                        constants++;}
                    else{
                        fprintf(outputfile, "%s\t\tType : Invalid\n", word);
                        invalids++;}
                    tokencount++;
                    break;
                case 5:
                    fprintf(outputfile, "%d.Token : ", tokencount+1);
                    j = 0;
                    while(!isDelimiter(line[i], 0) && !isalnum(line[i]) && !isalpha(line[i])){
                        word[j] = line[i];
                        j++;
                        i++;}
                    word[j] = '\0';
                    if(isOperator(word)){
                        fprintf(outputfile, "%s\t\t\tType : Operator\n", word);
                        operators++;}
                    else{
                        fprintf(outputfile, "%s\t\t\tType : Invalid\n", word);
                        invalids++;}
                    tokencount++;
                    break;
                default:
                    break;}
            }
        }
    }
    printf("Total tokens: %d\n", tokencount);
    printf("Keywords: %d\n", keywords);
    printf("Identifiers: %d\n", identifiers);
    printf("Constants: %d\n", constants);
    printf("Operators: %d\n", operators);
    printf("Special Characters: %d\n", specialchar);
    printf("Strings: %d\n", strings);
    printf("Invalids: %d\n", invalids);
    return(0);
}