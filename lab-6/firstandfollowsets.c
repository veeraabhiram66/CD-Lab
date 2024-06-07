
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char nonTerminal;
    char production[MAX][MAX];
    int noOfProductions;
} Rule;

typedef struct {
    char startSymbol;
    char nonTerminals[MAX];
    char terminals[MAX];
    Rule rules[MAX];
    int noOfRules;
} CFG;

typedef struct {
    char symbol;
    char first[MAX];
    char follow[MAX];
} firstFollow;

CFG cfg;
firstFollow table[MAX];

void print_terms()          // function to print terminals
{
    printf("Terminals    : {");
    for(int i = 0; i < strlen(cfg.terminals) - 1; i++)
        printf("%c, ", cfg.terminals[i]);
    printf("%c}\n", cfg.terminals[strlen(cfg.terminals) - 1]);
}

void print_non_terms()   // function to print non terminals
{
    printf("Non Terminals: {");
    for(int i = 0; i < strlen(cfg.nonTerminals) - 1; i++)
        printf("%c, ", cfg.nonTerminals[i]);
    printf("%c}\n", cfg.nonTerminals[strlen(cfg.nonTerminals) - 1]);
}

void print_cfg()     // function to print cfg
{
    printf("CFG:\n");
    printf("Start Symbol : %c\n", cfg.startSymbol);
    print_non_terms();
    print_terms();
    printf("Rules:\n");
    for(int i = 0; i < strlen(cfg.nonTerminals); i++)
    {
        printf("\t%c -> ", cfg.rules[i].nonTerminal);
        for(int j = 0; j < cfg.rules[i].noOfProductions - 1; j++)
        {
            printf("%s | ", cfg.rules[i].production[j]);
        }
        printf("%s", cfg.rules[i].production[cfg.rules[i].noOfProductions - 1]);
        printf("\n");
    }
    printf("\n");
}

int insert_non_term(char non_term)      // function to insert non terminals
{
    if(strchr(cfg.nonTerminals, non_term) == NULL)
    {
        cfg.nonTerminals[strlen(cfg.nonTerminals)] = non_term;
        return 0;
    }
    return 1;
}

void insert_term(char symbol)          // function to insert terminals
{
    if(strchr(cfg.terminals, symbol) == NULL)
        cfg.terminals[strlen(cfg.terminals)] = symbol;
}

void printTable(Rule table[][MAX], int n_nt, int n_t)        // function to print LL(1) table
{
    printf("LL(1) Table:\n");
    printf("\t\t");
    for(int i = 0; i < n_t; i++)
    {
        printf("%c\t\t", cfg.terminals[i]);
    }
    printf("\n");
    for(int i = 0; i < n_nt; i++)
    {
        printf("\t%c\t", cfg.nonTerminals[i]);
        for(int j = 0; j < n_t; j++)
        {
            if(table[i][j].production[0][0] != '\0')
                printf("%c->%s\t\t", cfg.nonTerminals[i], table[i][j].production[0]);
            else
                printf("\t\t");
        }
        printf("\n");
    }
}

int index_in_table(firstFollow table[], char symbol, int n_s)   // function to find index of a symbol in table
{
    for(int i = 0; i < n_s; i++)
        if(table[i].symbol == symbol)
            return i;
    printf("Trying to find index of %c in ", symbol);
    print_non_terms();
    exit(1);
}

int if_epsilon(char string[])    // function to check if a string contains epsilon
{
    for(int i = 0; i < strlen(string); i++)
        if(string[i] == '#')
            return 1;
    return 0;
}

char* remove_epsilon(char first[])   // function to remove epsilon from a string
{
    char *string = (char*)malloc(sizeof(char) * MAX);
    int l = strlen(first), j = 0;
    for(int i = 0; i < l; i++)
    {
        if(first[i] != '#')
            string[j] = first[i];
        j++;
    }
    return string;
}

int sets_union(char *src, char *dest, int changed)   // function to find union of two strings
{
    int l = strlen(src);
    for(int i = 0; i < strlen(dest); i++)
    {
        if(strchr(src, dest[i]) == NULL)
        {
            src[l] = dest[i];
            changed = 1;
            l++;
        }
    }
    return changed;
}

void print_first(firstFollow table[], int n_s)     // function to print first sets
{
    printf("First-Sets:\n");
    for(int i = 0; i < n_s; i++)
    {
        printf("\tFIRST(%c) = { ", table[i].symbol);
        for(int j = 0; j < strlen(table[i].first) - 1; j++)
            printf("%c, ", table[i].first[j]);
        printf("%c }\n", table[i].first[strlen(table[i].first) - 1]);
    }
}

void print_follow(firstFollow table[], int n_s)    // function to print follow sets
{
    printf("\nFollow-Sets:\n");
    for(int i = 0; i < n_s; i++)
    {
        printf("\tFOLLOW(%c) = { ", table[i].symbol);
        int n = strlen(table[i].follow);
        for(int j = 0; j < n - 1; j++)
            printf("%c, ", table[i].follow[j]);
        printf("%c }\n", table[i].follow[n - 1]);
    }
}

void first(CFG cfg)            // function to find first sets
{
    int n_nt = strlen(cfg.nonTerminals);
    int n_t = strlen(cfg.terminals);
    int n_s = n_nt + n_t;

    for(int i = 0; i < n_t; i++)    // for each (a ∈ T) FIRST(a) = ∅
    {
        table[i].symbol = cfg.terminals[i];     // table[i].symbol = a
        table[i].first[0] = cfg.terminals[i];   // table[i].first = {a}
    }
    for(int i = n_t; i < n_s; i++)  // for each (A ∈ N) FIRST(A) = ∅
    {
        table[i].symbol = cfg.nonTerminals[i - n_t];
        strcpy(table[i].first, "");
    }
    int changing = 1;     // for checking if any changes are made in the first sets
    while(changing)
    {
        changing = 0;            // if no changes are made, then exit the loop
        for(int i = 0; i < cfg.noOfRules; i++)      // for each production A -> α
        {
            for(int j = 0; j < cfg.rules[i].noOfProductions; j++)   // for each production A -> α in A -> α | β
            {
                char nonTerminal = cfg.rules[i].nonTerminal;      // nonTerminal for which we are finding the first set

                char prod[MAX];
                strcpy(prod, cfg.rules[i].production[j]);        //copying the production to prod

                int index = index_in_table(table, nonTerminal, n_s); // index of nonTerminal in table
                int k = 0, n = strlen(prod), for_first_x = 1;

                int x_index = index_in_table(table, prod[k], n_s);
                while((if_epsilon(table[x_index].first) && k <= n - 2) || for_first_x) // while FIRST(x) contains ε
                {
                    if(for_first_x)
                    {
                        for_first_x = 0;
                        k = -1;
                    }
                    x_index = index_in_table(table, prod[k + 1], n_s);   // index of x in table
                    char *x_first_set = remove_epsilon(table[x_index].first);  // FIRST(x) - {ε}
                    changing = sets_union(table[index].first, x_first_set, changing);  // FIRST(A) = FIRST(A) ∪ FIRST(x)
                    k++;
                }
                if(k == n - 1 && if_epsilon(table[x_index].first))  // if FIRST(x) contains ε and x is the last symbol in production
                {
                    char *epsilon = "#";
                    changing = sets_union(table[index].first, epsilon, changing); // FIRST(A) = FIRST(A) ∪ {ε}
                }
            }
        }
    }
    print_first(table, n_s);   // print first sets
}

void follow(CFG cfg)  //function to find follow sets
{
    int n_nt = strlen(cfg.nonTerminals);
    int n_t = strlen(cfg.terminals);
    int n_s = n_nt + n_t;

    for(int i = 0; i < n_t; i++)    // for each (a ∈ T) FIRST(a) = ∅
    {
        table[i].symbol = cfg.terminals[i];
        strcpy(table[i].follow, "");
    }
    for(int i = n_t; i < n_s; i++)  // for each (A ∈ N) FIRST(A) = ∅
    {
        table[i].symbol = cfg.nonTerminals[i - n_t];
        strcpy(table[i].follow, "");
    }
    for(int i = 0; i < n_s; i++)    // FOLLOW(S) = {$}
    {
        if(table[i].symbol == cfg.startSymbol)
            table[i].follow[0] = '$';
    }
    int changing = 1;
    while(changing)
    {
        changing = 0;
        for(int i = 0; i < cfg.noOfRules; i++)   // for each production A -> α
        {
            for(int j = 0; j < cfg.rules[i].noOfProductions; j++) // for each production A -> α in A -> α | β
            {
                char nonTerminal = cfg.rules[i].nonTerminal;  // nonTerminal for which we are finding the follow set
                char *prod = remove_epsilon(cfg.rules[i].production[j]); //copying the production to prod
                if(strlen(prod) == 0)
                    continue;

                int index = index_in_table(table, nonTerminal, n_s); // index of nonTerminal in table
                int k = 0, n = strlen(prod), for_first_x = 1;

                int x_index = index_in_table(table, prod[strlen(prod)-1], n_s);
                changing = sets_union(table[x_index].follow, table[index].follow, changing); // FOLLOW(x) = FOLLOW(x) ∪ FOLLOW(A)

                char *rest = table[index].follow;
                // for each x in α in reverse order (α = xβ) for finding FOLLOW(x) of nonTerminal
                for(int k = strlen(prod)-1; k >= 1; k--)  
                {
                    int x_i_index = index_in_table(table, prod[k], n_s);
                    char *x_i_first_set = table[x_i_index].first;
                    char x_i_1 = prod[k - 1];
                    int x_i_1_index = index_in_table(table, prod[k - 1], n_s);
                    if(if_epsilon(x_i_first_set))   // if FIRST(x) contains ε
                    {
                        char *x_i_first_set = remove_epsilon(table[x_i_index].first);  // FIRST(x) - {ε}
                        changing = sets_union(table[x_i_1_index].follow, x_i_first_set, changing);
                        changing = sets_union(table[x_i_1_index].follow, rest, changing);  // FOLLOW(x) = FOLLOW(x) ∪ FOLLOW(A)
                    }
                    else
                    {
                        changing = sets_union(table[x_i_1_index].follow, x_i_first_set, changing);  // FOLLOW(x) = FOLLOW(x) ∪ FIRST(x)
                    }
                    rest = table[x_i_index].follow;   // rest = FOLLOW(x)
                }
            }
        }
    }
    print_follow(table, n_s);   // print follow sets
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char str[MAX];
    int ruleCount = 0;
    if (argc != 2)            // checking if file is given as command line argument
    {
        printf("Error file!\n");
        return 1;
    }
    fp = fopen(argv[1], "r");    // opening file
    if(fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }
    while(fgets(str, MAX, fp))    // reading file line by line
    {
        ruleCount++;
        Rule rule;

        rule.nonTerminal = strtok(str, " =\n")[0];
        strcpy(rule.production[0], strtok(NULL, " =\n"));   // copying production to rule.production[0]
        // for inserting non terminal
        int exist = insert_non_term(rule.nonTerminal);   // checking if non terminal already exists
        if(!exist)
            cfg.rules[strlen(cfg.nonTerminals) - 1].nonTerminal = rule.nonTerminal;  
        if(ruleCount == 1)
            cfg.startSymbol = rule.nonTerminal;   
        // for inserting production
        for(int i = 0; i < strlen(cfg.nonTerminals) ; i++)  // checking if non terminal already exists
        {
            if(cfg.rules[i].nonTerminal == rule.nonTerminal)
            {
                int j = cfg.rules[i].noOfProductions;   // inserting production
                strcpy(cfg.rules[i].production[j], rule.production[0]);
                cfg.rules[i].noOfProductions++;
                break;
            }
        }
        // for inserting terminals
        for(int i = 0; i < strlen(rule.production[0]); i++)
        {
            if(!isupper(rule.production[0][i])) //  && rule.production[0][i] != '#'
            {
                insert_term(rule.production[0][i]);
            }
        }
    }
    cfg.noOfRules = ruleCount;     // number of rules
    print_cfg();                   // print cfg
    first(cfg);                   // find first sets
    follow(cfg);                 // find follow sets

    return 0;
}