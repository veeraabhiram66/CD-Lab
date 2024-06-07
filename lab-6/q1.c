//Given a CFG as an input file in which each line is having exactly one production rule and epsilon as #
// Write a c program to compute the first and follow sets of both T & NT (Terminals & Non-terminals) in the given CFG. (NT-Capital letters, T-small letters).

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX 100

int n;
char prod[MAX][MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int first_count[MAX];
int follow_count[MAX];
char term[MAX];
char non_term[MAX];

//read the grammar from the file
void read_grammar(char *filename, char *argv[])
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(0);
    }
    //read grammar based on tokens
    char *token;
    char line[MAX];
    n = 0;
    while(fgets(line, MAX, fp) != NULL)
    {
        token = strtok(line, " ");
        strcpy(prod[n], token);
        token = strtok(NULL, " ");
        while(token != NULL)
        {
            strcat(prod[n], " ");
            strcat(prod[n], token);
            token = strtok(NULL, " ");
        }
        n++;
    }
    fclose(fp);

}
//print the grammar
void print_grammar()
{
    printf("The grammar is:\n");
    for(int i=0; i<n; i++)
    {
        printf("%s", prod[i]);
    }
    printf("\n");
}

//Identify the terminal symbols (usually lowercase letters) and non-terminal symbols (usually uppercase letters) in your grammar.
void identify_symbols()
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<strlen(prod[i]); j++)
        {
            if(islower(prod[i][j]))
            {
                if(strchr(term, prod[i][j]) == NULL)
                {
                    char *temp = (char *)malloc(sizeof(char));
                    temp[0] = prod[i][j];
                    strcat(term, temp);
                }
            }
            else if(isupper(prod[i][j]))
            {
                if(strchr(non_term, prod[i][j]) == NULL)
                {
                    char *temp = (char *)malloc(sizeof(char));
                    temp[0] = prod[i][j];
                    strcat(non_term, temp);
                }
            }
        }
    }
}


//Initialize a flag, changed, to track changes in the FIRST sets.
int changed = 1;
//Iterate over the grammar productions until no changes occur in the FIRST sets.
void compute_first_set()
{
//     For each production, consider the leftmost symbol:
// If it's a terminal symbol, add it to the FIRST set of the corresponding non-terminal.
// If it's a non-terminal symbol, consider the right-hand side of the production:
// Add the FIRST set of the right-hand side symbols to the FIRST set of the current non-terminal.
// If epsilon ('#') is in the FIRST set of all right-hand side symbols, add epsilon to the FIRST set of the current non-terminal.
//Continue this process until no changes occur in any FIRST set.

    while(changed)
    {
        changed = 0;
        for(int i=0; i<n; i++)
        {
            char *token = strtok(prod[i], " ");
            char *lhs = token;
            token = strtok(NULL, " ");
            while(token != NULL)
            {
                if(islower(token[0]))
                {
                    if(strchr(first[i], token[0]) == NULL)
                    {
                        char *temp = (char *)malloc(sizeof(char));
                        temp[0] = token[0];
                        strcat(first[i], temp);
                        first_count[i]++;
                        changed = 1;
                    }
                    break;
                }
                else if(isupper(token[0]))
                {
                    int j;
                    for(j=0; j<n; j++)
                    {
                        if(prod[j][0] == token[0])
                        {
                            break;
                        }
                    }
                    for(int k=0; k<first_count[j]; k++)
                    {
                        if(strchr(first[i], first[j][k]) == NULL)
                        {
                            char *temp = (char *)malloc(sizeof(char));
                            temp[0] = first[j][k];
                            strcat(first[i], temp);
                            first_count[i]++;
                            changed = 1;
                        }
                    }
                    if(strchr(first[j], '#') == NULL)
                    {
                        break;
                    }
                }
                else if(token[0] == '#')
                {
                    if(strchr(first[i], token[0]) == NULL)
                    {
                        char *temp = (char *)malloc(sizeof(char));
                        temp[0] = token[0];
                        strcat(first[i], temp);
                        first_count[i]++;
                        changed = 1;
                    }
                    break;
                }
                token = strtok(NULL, " ");
            }
        }
    }
}

//print the first set
void print_first_set()
{
    printf("The first set is:\n");
    for(int i=0; i<n; i++)
    {
        printf("FIRST(%c) = ", prod[i][0]);
        for(int j=0; j<first_count[i]; j++)
        {
            if(prod[i][j] == prod[i+1][j])
            {
                printf("{%c , %c}", first[i][j], first[i+1][j]);
                i++;
            }
            if(j != first_count[i]-1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }
}
void compute_follow_set()
{
    //Add $ (the end-of-input marker) to the FOLLOW set of the start symbol (the left-hand side of the first production).
    strcat(follow[0], "$");
    follow_count[0]++;
    // For each symbol X in the right-hand side of the production:
    // If X is a non-terminal (a non-terminal symbol):
    // Add all symbols from the FIRST set of the symbols that follow X in the production to the FOLLOW set of X, except for ε.
    // If ε is in the FIRST set of all symbols that follow X in the production, add the symbols from the FOLLOW set of the left-hand side non-terminal of the production to the FOLLOW set of X.
    //If a non-terminal A appears at the end of any right-hand side (i.e., A is the rightmost symbol in a production), add all symbols from the FOLLOW set of the left-hand side non-terminal of that production to the FOLLOW set of A.
    
}

void print_follow_set()
{
    printf("The follow set is:\n");
    for(int i=0; i<n; i++)
    {
        printf("FOLLOW(%c) = ", prod[i][0]);
        for(int j=0; j<follow_count[i]; j++)
        {
            if(prod[i][j] == prod[i+1][j])
            {
                printf("{%c , %c}", follow[i][j], follow[i+1][j]);
                i++;
            }
            if(j != follow_count[i]-1)
            {
                printf(", ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Error opening file!\n");
        exit(0);
    }
    read_grammar(argv[1], argv);
    print_grammar();
    identify_symbols();
    compute_first_set();
    print_first_set();
    compute_follow_set();
    print_follow_set();
    return 0;

}