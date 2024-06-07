//Given a CFG which is LL(1) as an input file where each line has exactly one production rule, Write a C program to compute and print the LL(1) parsing table. 
//Note: (Nonterminals -Capital letters, Terminals - small letters).
// V = S$
// S = aAS
// S = c
// A = ba
// A = SB
// B = bA
// B = S

// Note: starting symbol is V here.

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//reading the input grammar from file

void read_grammar(char *filename, char *grammar[])
{
    //read the grammar from grammar.txt file
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error\n");
        exit(0);
    }
    char line[100];
    int i = 0;
    while (fgets(line, 100, fp) != NULL)
    {
        grammar[i] = (char *)malloc(sizeof(char) * 100);
        strcpy(grammar[i], line);
        i++;
    }
    grammar[i] = NULL;
    fclose(fp);
}

//printing the grammar

void print_grammar(char *grammar[])
{
    int i = 0;
    while (grammar[i] != NULL)
    {
        printf("%s", grammar[i]);
        i++;
    }
}
 
void merge_first(char *temp, char *first){
    //iterate through the first set of the current non-terminal
    //if the character is not present in the first set of the LHS, add it to the first set of the LHS
    int i = 0;
    while (first[i] != '\0')
    {
        int j = 0;
        while (temp[j] != '\0')
        {
            if (first[i] == temp[j])
            {
                break;
            }
            j++;
        }
        if (temp[j] == '\0')
        {
            temp[j] = first[i];
            temp[j + 1] = '\0';
        }
        i++;
    }
    strcpy(first, temp);
}

//compute the first set of all non-terminals and terminals
void compute_first(char *grammar[], char *first[]){
    //create an array and store the first set of all non-terminals and terminals
    int i = 0;
    first[i] = (char *)malloc(sizeof(char) * 100);
    first[i][0] = '$';
    i++;
    //iterate through the production rules
    //tokenize the production rules into lhs and rhs
    //if the first character of rhs is a terminal, add it to the first set
    // Handle non-terminals in the RHS
    // Initialize index variable j to 0
    // While First set of the current non-terminal (RHS[j]) is not NULL
        // Create a temporary buffer (temp) to hold the current First set
        // Copy First set of the current non-terminal to temp
        // Merge temp with the First set of the LHS
        // Increment j
        // If ε is not in the First set of the current non-terminal, stop loop

    while (grammar[i] != NULL)
    {
        char *line = grammar[i];
        char *lhs = strtok(line, " ");
        char *rhs = strtok(NULL, " ");
        if (rhs[0] >= 'a' && rhs[0] <= 'z')
        {
            first[i] = (char *)malloc(sizeof(char) * 100);
            first[i][0] = rhs[0];
            first[i][1] = '\0';
        }
        else if (rhs[0] >= 'A' && rhs[0] <= 'Z')
        {
            int j = 0;
            while (first[rhs[0] - 'A'][j] != '\0')
            {
                char *temp = (char *)malloc(sizeof(char) * 100);
                strcpy(temp, first[rhs[0] - 'A']);
                merge_first(temp, first[i]);
                j++;
                if (first[rhs[0] - 'A'][j] == '\0')
                {
                    if (temp[0] == '$')
                    {
                        j = 1;
                        while (first[rhs[j] - 'A'][0] != '\0')
                        {
                            char *temp = (char *)malloc(sizeof(char) * 100);
                            strcpy(temp, first[rhs[j] - 'A']);
                            merge_first(temp, first[i]);
                            j++;
                        }
                    }
                }
            }
        }
    }

}


//printing the first set of all non-terminals and terminals
//remove the unwanted characters from the first set

void print_first(char *first[])
{
    int i = 0;
    while (first[i] != NULL)
    {
        printf("FIRST(%c) = {%s}\n", i + 'A', first[i]);
        i++;
    }
}


//compute the follow set of all non-terminals and terminals

void compute_follow(char *grammar[], char *first[], char *follow[])
{
    int i = 0;
    while (grammar[i] != NULL)
    {
        char *line = grammar[i];
        char *lhs = strtok(line, " ");
        char *rhs = strtok(NULL, " ");
        int j = 0;
        while (rhs[j] != '\0')
        {
            if (rhs[j] >= 'A' && rhs[j] <= 'Z')
            {
                if (rhs[j + 1] == '\0')
                {
                    int k = 0;
                    while (follow[lhs[0] - 'A'][k] != '\0')
                    {
                        follow[rhs[j] - 'A'] = (char *)malloc(sizeof(char) * 100);
                        follow[rhs[j] - 'A'][k] = follow[lhs[0] - 'A'][k];
                        k++;
                    }
                }
                else if (rhs[j + 1] >= 'a' && rhs[j + 1] <= 'z')
                {
                    follow[rhs[j] - 'A'] = (char *)malloc(sizeof(char) * 100);
                    follow[rhs[j] - 'A'][0] = rhs[j + 1];
                }
                else if (rhs[j + 1] >= 'A' && rhs[j + 1] <= 'Z')
                {
                    int k = 0;
                    while (first[rhs[j + 1] - 'A'][k] != '\0')
                    {
                        follow[rhs[j] - 'A'] = (char *)malloc(sizeof(char) * 100);
                        follow[rhs[j] - 'A'][k] = first[rhs[j + 1] - 'A'][k];
                        k++;
                    }
                }
            }
            j++;
        }
        i++;
    }
}

//printing the follow set of all non-terminals and terminals

void print_follow(char *follow[])
{
    int i = 0;
    while (follow[i] != NULL)
    {
        printf("FOLLOW(%c) = {%s}\n", i + 'A', follow[i]);
        i++;
    }
}

//compute the parsing table

void compute_table(char *grammar[], char *first[], char *follow[], char *table[][100])
{
    int i = 0;
    while (grammar[i] != NULL)
    {
        char *line = grammar[i];
        char *lhs = strtok(line, " ");
        char *rhs = strtok(NULL, " ");
        int j = 0;
        while (rhs[j] != '\0')
        {
            if (rhs[j] >= 'a' && rhs[j] <= 'z')
            {
                int k = 0;
                while (first[rhs[j] - 'a'][k] != '\0')
                {
                    table[lhs[0] - 'A'][rhs[j] - 'a'] = (char *)malloc(sizeof(char) * 100);
                    table[lhs[0] - 'A'][rhs[j] - 'a'][k] = rhs[0];
                    k++;
                }
            }
            else if (rhs[j] >= 'A' && rhs[j] <= 'Z')
            {
                int k = 0;
                while (first[rhs[j] - 'A'][k] != '\0')
                {
                    table[lhs[0] - 'A'][rhs[j] - 'A'] = (char *)malloc(sizeof(char) * 100);
                    table[lhs[0] - 'A'][rhs[j] - 'A'][k] = rhs[0];
                    k++;
                }
            }
            j++;
        }
        i++;
    }
}

//printing the parsing table

void print_table(char *table[][100])
{
    printf("\nParsing Table\n");
    printf("-------------------------------------------------\n");
    printf("Non-Terminal\tTerminal\tProduction\n");
    printf("-------------------------------------------------\n");
    int i = 0;
    while (table[i] != NULL)
    {
        int j = 0;
        while (table[i][j] != NULL)
        {
            printf("%c\t\t%c\t\t%s\n", i + 'A', j + 'a', table[i][j]);
            j++;
        }
        i++;
    }
    printf("-------------------------------------------------\n");
}

//parsing the input string

void parse(char *table[][100], char *input)
{
    char *stack = (char *)malloc(sizeof(char) * 100);
    stack[0] = 'V';
    int top = 0;
    int i = 0;
    while (input[i] != '\0')
    {
        if (input[i] >= 'a' && input[i] <= 'z')
        {
            if (stack[top] == input[i])
            {
                top--;
                i++;
            }
            else
            {
                printf("Error\n");
                exit(0);
            }
        }
        else if (input[i] >= 'A' && input[i] <= 'Z')
        {
            if (table[stack[top] - 'A'][input[i] - 'a'] != NULL)
            {
                char *rhs = table[stack[top] - 'A'][input[i] - 'a'];
                top--;
                int j = 0;
                while (rhs[j] != '\0')
                {
                    stack[++top] = rhs[j];
                    j++;
                }
            }
            else
            {
                printf("Error\n");
                exit(0);
            }
        }
    }
    if (stack[top] == '$')
    {
        printf("Accepted\n");
    }
    else
    {
        printf("Error\n");
    }
}

int main()
{
    char *grammar[100];
    read_grammar("grammar.txt", grammar);
    printf("Grammar\n");
    printf("-------------------------------------------------\n");
    print_grammar(grammar);
    printf("\n-------------------------------------------------\n");
    char *first[26];
    compute_first(grammar, first);
    printf("\nFirst\n");
    printf("-------------------------------------------------\n");
    print_first(first);
    printf("-------------------------------------------------\n");
    char *follow[26];
    compute_follow(grammar, first, follow);
    printf("\nFollow\n");
    printf("-------------------------------------------------\n");
    print_follow(follow);
    printf("-------------------------------------------------\n");
    char *table[26][100];
    compute_table(grammar, first, follow, table);
    print_table(table);
    char input[100];
    printf("Enter the input string: ");
    scanf("%s", input);
    parse(table, input);
    return 0;
}