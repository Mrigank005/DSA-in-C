#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int stack[MAX_SIZE];
int top = -1;

int tempStack[MAX_SIZE];
int tempTop = -1;

void push(int data) {
    if (top == MAX_SIZE - 1) {
        printf("Stack overflow! Cannot push to a full stack.\n");
        return;
    }
    stack[++top] = data;
    printf("%d pushed to stack\n", data);
}

int pop() {
    if (top == -1) {
        printf("Stack underflow! Cannot pop from an empty stack.\n");
        return -1;
    }
    return stack[top--];
}

void pushTemp(int data) {
    if (tempTop == MAX_SIZE - 1) {
        printf("Temporary stack overflow!\n");
        return;
    }
    tempStack[++tempTop] = data;
}

int popTemp() {
    if (tempTop == -1) {
        printf("Temporary stack underflow!\n");
        return -1;
    }
    return tempStack[tempTop--];
}

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == MAX_SIZE - 1;
}

void displayStack() {
    if (isEmpty()) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements (Top to Bottom): ");
    for (int i = top; i >= 0; i--) {
        printf("%d ", stack[i]);
    }
    printf("\n");
}

void reverseStack() {
    if (isEmpty()) {
        printf("Stack is empty. Nothing to reverse.\n");
        return;
    }

    printf("Reversing stack using temporary stack...\n");
    
    // Move all elements from original stack to temp stack
    while (!isEmpty()) {
        pushTemp(pop());
    }
    
    // Move all elements back from temp stack to original stack (now reversed)
    while (tempTop != -1) {
        push(popTemp());
    }
    
    printf("Stack has been reversed.\n");
}

int main() {
    int choice, data, n;

    printf("Enter the number of elements to add to the stack: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Number of elements exceeds stack capacity. Setting to maximum size %d.\n", MAX_SIZE);
        n = MAX_SIZE;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &data);
        push(data);
    }
    displayStack();

    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display Stack\n");
        printf("4. Reverse Stack\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (isFull()) {
                    printf("Stack is full. Cannot push more elements.\n");
                    break;
                }
                printf("Enter the element to push: ");
                scanf("%d", &data);
                push(data);
                displayStack();
                break;

            case 2:
                data = pop();
                if (data != -1) {
                    printf("%d popped from stack\n", data);
                }
                displayStack();
                break;

            case 3:
                displayStack();
                break;

            case 4:
                reverseStack();
                displayStack();
                break;

            case 5:
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}