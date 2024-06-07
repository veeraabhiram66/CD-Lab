//Given a CFG which is LL(1) as an input file where each line has exactly one production rule
// Write a C program to compute and print the LL(1) parsing table. 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char nonterminals;
    char productions[MAX][MAX];
    int numproductions;
} Rule;

typedef struct {
    char start;
    char nonterminals[MAX];
    char terminals[MAX];
    Rule rules[MAX];
    int numrules;
} CFG;

void print_grammar(CFG cfg)
{
    printf("The CFG is:\n");
    printf("Start: %c\n", cfg.start);
    printf("Non-terminals: %s\n", cfg.nonterminals);
    printf("Terminals: %s\n", cfg.terminals);
    printf("Rules:\n");
    for (int i = 0; i < cfg.numrules; i++)
    {
        printf("%c", cfg.rules[i].nonterminals);
        for (int j = 0; j < cfg.rules[i].numproductions; j++)
        {
            printf(" -> %s \n ", cfg.rules[i].productions[j]);
        }
        printf("\r");
    }
}

char *next_terminal(CFG *cfg, char *prod)
{
    char next[MAX];
    memset(next, 0, sizeof(next));
    if (isupper(prod[0]))
    {
        int n = strchr(cfg->nonterminals, prod[0]) - cfg->nonterminals;
        for (int i = 0; i < cfg->rules[n].numproductions; i++)
        {
            strcat(next, next_terminal(cfg, cfg->rules[n].productions[i]));
        }
    }
    else
    {
        next[0] = prod[0];
    }
    char *ret = malloc(sizeof(next));
    strcpy(ret, next);
    return ret;
}

void compute_ll1_table(CFG cfg)
{
    int n_nt = strlen(cfg.nonterminals);
    int n_t = strlen(cfg.terminals);
    int n_r = cfg.numrules;
    Rule table[n_nt][n_t];
    
    int total = 0;
    for (int i = 0; i < n_r; i++)
    {
        for (int j = 0; j < cfg.rules[i].numproductions; j++)
        {
            char *next = next_terminal(&cfg, cfg.rules[i].productions[j]);
            for (int k = 0; k < strlen(next); k++)
            {
                int n = strchr(cfg.nonterminals, cfg.rules[i].nonterminals) - cfg.nonterminals;
                int m = strchr(cfg.terminals, next[k]) - cfg.terminals;
                strcpy(table[n][m].productions[0], cfg.rules[i].productions[j]);
                printf("(%c, %c): %c -> %s\n", cfg.rules[i].nonterminals, next[k], cfg.rules[i].nonterminals, table[n][m].productions[0]);
                total++;
            }
        }
    }
    printf("Total: %d\n", total);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s <file>\n", argv[0]);
        return 1;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    CFG cfg;
    int n = 0, end = 0;
    char line[MAX];
    while (fgets(line, MAX, fp) != NULL)
    {
        char *token = strtok(line, " =\n");
        if (strchr(cfg.nonterminals, token[0]) == NULL) {
            strncat(cfg.nonterminals, token, 1);
            cfg.rules[end].nonterminals = token[0];
            cfg.rules[end].numproductions = 0;
            end++;
        }
        n = strchr(cfg.nonterminals, token[0]) - cfg.nonterminals;

        token = strtok(NULL, " =\n");
        for (int i = 0; i < strlen(token); i++)
        {
            if (strchr(cfg.terminals, token[i]) == NULL && !isupper(token[i]))
                strncat(cfg.terminals, token + i, 1);
        }
        strcpy(cfg.rules[n].productions[cfg.rules[n].numproductions], token);
        cfg.rules[n].numproductions++;
    }
    cfg.start = cfg.rules[0].nonterminals;
    cfg.numrules = end;
    print_grammar(cfg);
    fclose(fp);
    compute_ll1_table(cfg);
    return 0;
}