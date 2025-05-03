#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_SIZE 100

// Stack implementation using array
char stack[MAX_SIZE];
int top = -1;

void push(char item) {
    if (top >= MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = item;
}

char pop() {
    if (top < 0) {
        printf("Stack Underflow\n");
        return '\0';
    }
    return stack[top--];
}

char peek() {
    if (top < 0) {
        return '\0';
    }
    return stack[top];
}

int isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int precedence(char op) {
    switch(op) {
        case '^': return 4;
        case '*':
        case '/': return 3;
        case '+':
        case '-': return 2;
        default: return 0;
    }
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, j = 0;
    char ch, x;

    push('('); // Push initial '(' to stack
    strcat(infix, ")"); // Add ')' to end of infix expression

    ch = infix[i];
    while (ch != '\0') {
        if (ch == '(') {
            push(ch);
        } 
        else if (isalnum(ch)) { // If operand, add to output
            postfix[j++] = ch;
        } 
        else if (isOperator(ch)) { // If operator
            while (precedence(ch) <= precedence(peek())) {
                postfix[j++] = pop();
            }
            push(ch);
        } 
        else if (ch == ')') { // If ')', pop until '('
            x = pop();
            while (x != '(') {
                postfix[j++] = x;
                x = pop();
            }
        }
        i++;
        ch = infix[i];
    }

    postfix[j] = '\0'; // Null terminate the postfix string
}

int main() {
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("Enter an infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}