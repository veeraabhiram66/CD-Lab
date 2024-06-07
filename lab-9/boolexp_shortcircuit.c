// Given a boolean expression as an input, write a program to generate intermediate code for that boolean expression by using short circuit evaluation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tempCount = 0;
int labelCount = 0;

char* generateTempVar() {
    char* tempVar = (char*)malloc(10);
    snprintf(tempVar, 10, "t%d", tempCount++);
    return tempVar;
}

char* generateLabel() {
    char* label = (char*)malloc(10);
    snprintf(label, 10, "L%d", labelCount++);
    return label;
}

void generateIntermediateCode(char* expr) {
    char* token = strtok(expr, " ");
    char* result = generateTempVar();
    char* nextLabel = generateLabel();
    char* trueLabel = generateLabel();
    char* falseLabel = generateLabel();

    while (token != NULL) {
        if (strcmp(token, "&&") == 0) {
            char* op1 = generateTempVar();
            char* op2 = generateTempVar();
            printf("if %s goto %s\n", op1, trueLabel);
            printf("%s = 0\n", result);
            printf("goto %s\n", falseLabel);
            printf("%s: %s = 1\n", trueLabel, result);
            printf("%s: ", falseLabel);
        } else if (strcmp(token, "||") == 0) {
            char* op1 = generateTempVar();
            char* op2 = generateTempVar();
            printf("if %s goto %s\n", op1, trueLabel);
            printf("if %s goto %s\n", op2, trueLabel);
            printf("%s = 0\n", result);
            printf("goto %s\n", falseLabel);
            printf("%s: %s = 1\n", trueLabel, result);
            printf("%s: ", falseLabel);
        } else {
            // Assuming it's an operand (variable or constant)
            char* operand = token;
            printf("%s = %s\n", result, operand);
        }
        token = strtok(NULL, " ");
    }
    printf("goto %s\n", nextLabel);
    printf("%s: %s = 1\n", nextLabel, result);
}

int main() {
    char expression[100];

    printf("Enter a boolean expression (use '&&' and '||'): ");
    fgets(expression, sizeof(expression), stdin);

    // Remove trailing newline character
    expression[strcspn(expression, "\n")] = 0;

    printf("Intermediate Code:\n");
    generateIntermediateCode(expression);

    return 0;
}
