#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack implementation using array
int stack[MAX_SIZE];
int top = -1;

void push(int item) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

int pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack[top--];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int evaluatePostfix(char* postfix) {
    int i = 0;
    char ch;
    int operand1, operand2, result;

    while ((ch = postfix[i]) != '\0') {
        if (isdigit(ch)) {
            // If character is digit, push to stack (convert char to int)
            push(ch - '0');
        } 
        else if (isOperator(ch)) {
            // Pop two operands and perform operation
            operand2 = pop();
            operand1 = pop();
            
            switch(ch) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
                case '^': result = 1;
                          for (int j = 0; j < operand2; j++)
                              result *= operand1;
                          break;
            }
            push(result);
        }
        i++;
    }
    return pop(); // Final result
}

int main() {
    char postfix[MAX_SIZE];

    printf("Enter postfix expression (use single-digit operands): ");
    scanf("%s", postfix);

    int result = evaluatePostfix(postfix);
    printf("Result: %d\n", result);

    return 0;
}