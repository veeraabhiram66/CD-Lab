/*
Lab-2
Name: P.Veera Abhiram
Roll.no:CS21B2026
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void checkall(char ch, int *vow, int *cons, int *digits, int *others)
{
    if (isalpha(ch))
    {
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U')
        {
            (*vow)++;
        } 
        else
        {
            (*cons)++;
        }
    } 
    else if (isdigit(ch))
    {
    (*digits)++;
    }
    else
    {
    (*others)++;
    }
}

int main( int argc, char *argv[]) {

    FILE *fp;
    char buffer[500];
    int l = 0, w = 0, c = 0, vow = 0, cons = 0, digits = 0, others = 0;

    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("file not opening\n");
    }
    else{
    while (fgets(buffer, 1000, fp) != NULL)
    {
        l++;
        c+=strlen(buffer);
         
        for (int i = 0; i<strlen(buffer); i++)
        {
            checkall(buffer[i], &vow, &cons, &digits, &others);
        }
        char *token = strtok(buffer, " \t\n");

        while (token != NULL) {
            w++;
            token = strtok(NULL, " \t\n");
        }
    }
    }
    fclose(fp);
    
    printf("Characters: %d\t", c);
    printf("Words: %d\t", w);
    printf("Lines: %d\n", l);
    
    printf("vow: %d\t", vow);
    printf("cons: %d\t", cons);
    printf("Digits: %d\t", digits);
    printf("Other characters: %d\t", others);

    return 0;
}