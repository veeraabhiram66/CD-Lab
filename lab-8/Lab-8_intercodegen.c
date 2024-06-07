/*
Roll.No:CS21B2026
Name:P.Veera Abhiram
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Stack {
    int top;
    unsigned capacity;
    char* array;
};

struct Stack* createStack(unsigned capacity);
int isEmpty(struct Stack* stack);
void push(struct Stack* stack, char item);
char pop(struct Stack* stack);
char peek(struct Stack* stack);
int isOperator(char ch);
int precedence(char ch);
char * infixtopostfix(char* infix);
void three_add_gen(char * str);

int main() {
    char infix[100];
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    char * str = infixtopostfix(infix);
    three_add_gen(str);
    return 0;
}


struct Stack* createStack(unsigned capacity) {                 //creating stack using array 
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isEmpty(struct Stack* stack) {                   
    return stack->top == -1;
}

void push(struct Stack* stack, char item) {
    stack->array[++stack->top] = item;
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '$'; 
}

char peek(struct Stack* stack) {             //returns the top element of the stack
    if (!isEmpty(stack)) {
        return stack->array[stack->top];
    }
    return '$'; 
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int precedence(char ch) {               //returns the precedence of the operator
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    return 0;
}

char* infixtopostfix(char* infix) {                        //converts infix to postfix
    int i, j;
    struct Stack* stack = createStack(strlen(infix));
    if (!stack) {
        printf("Memory error\n");
        return NULL;
    }
    
    char* postfix = (char*)malloc((strlen(infix) + 1) * sizeof(char));
    if (!postfix) {
        printf("Memory error\n");
        free(stack);
        return NULL;
    }

    for (i = 0, j = 0; infix[i]; i++) {                 //traversing the infix expression
        if (isalnum(infix[i]))
            postfix[j++] = infix[i];
        else if (infix[i] == '(')                 //if the character is '(' then push it into the stack
            push(stack, infix[i]);
        else if (infix[i] == ')') {              //if the character is ')' then pop the elements from the stack and add it to the postfix expression
            while (peek(stack) != '$' && peek(stack) != '(')
                postfix[j++] = pop(stack);
            if (peek(stack) == '(')
                pop(stack);
        } else {                                   //if the character is an operator then pop the elements from the stack and add it to the postfix expression
            while (!isEmpty(stack) && precedence(infix[i]) <= precedence(peek(stack)))
                postfix[j++] = pop(stack);
            push(stack, infix[i]);
        }
    }

    while (!isEmpty(stack))
        postfix[j++] = pop(stack);

    postfix[j] = '\0';
    free(stack);
    return postfix;
}

void three_add_gen(char * str) {                //generates three address code
    struct Stack * stk = createStack(strlen(str));
    int v = 0;

    for(int i=0;i<strlen(str);i++) {      //traversing the postfix expression
        if(!isOperator(str[i])) {
            push(stk, str[i]);
        }
        else {                        //if the character is an operator then pop the elements from the stack and generate three address code
            v++;
            char c1 = pop(stk);
            char c2 = pop(stk);
            if((c1 >= 97 && c1 <= 122) && (c2 >= 97 && c2 <= 122)) {   //if both the characters are variables
                printf("t%d = %c %c %c \n", v, c2, str[i], c1);
            }
            else {                             //if one of the character is a variable
                if(c1 >= 97 && c1 <= 122) {
                    printf("t%d = t%c %c %c \n", v, c2, str[i], c1);
                }
                else if(c2 >= 97 && c2 <= 122) {              
                    printf("t%d = %c %c t%c \n", v, c2, str[i], c1);
                }
                else {                        //if both the characters are not variables
                    printf("t%d = t%c %c t%c \n", v, c2, str[i], c1);
                }
            }
            v = v + '0';
            push(stk, v);
            v = v - '0';
        }
    }
}