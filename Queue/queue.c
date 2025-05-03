#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Queue {
    int *queue;
    int front;
    int rear;
    int capacity;
};

void initializeQueue(struct Queue *q, int capacity) {
    q->queue = (int *)malloc(capacity * sizeof(int));
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
}

int isEmpty(struct Queue *q) {
    return (q->front == -1);
}

int isFull(struct Queue *q) {
    return (q->rear == q->capacity - 1);
}

void insert(struct Queue *q, int data) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->queue[q->rear] = data;
    printf("Inserted %d into the queue\n", data);
}

int delete(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    printf("Deleted element: %d\n", data);
    return data;
}

void display(struct Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->queue[i]);
    }
    printf("\n");
}

void freeQueue(struct Queue *q) {
    free(q->queue);
    q->queue = NULL;
}

int isPalindromeArray(char *str) {
    int length = strlen(str);
    for (int i = 0; i < length/2; i++) {
        if (tolower(str[i]) != tolower(str[length-1-i])) {
            return 0;
        }
    }
    return 1;
}

int isPalindromeQueue(char *str) {
    struct Queue q;
    int length = strlen(str);
    initializeQueue(&q, length);
    
    // Insert characters into queue
    for (int i = 0; i < length; i++) {
        insert(&q, tolower(str[i]));
    }
    
    // Check palindrome by comparing with original string
    for (int i = length-1; i >= 0; i--) {
        if (tolower(str[i]) != delete(&q)) {
            freeQueue(&q);
            return 0;
        }
    }
    
    freeQueue(&q);
    return 1;
}

void queueOperations(struct Queue *q) {
    int choice, element;
    
    do {
        printf("\nQueue Operations Menu:\n");
        printf("1. Insert an element\n");
        printf("2. Delete an element\n");
        printf("3. Display queue\n");
        printf("4. Return to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                if (isFull(q)) {
                    printf("Queue is full. Cannot insert.\n");
                } else {
                    printf("Enter element to insert: ");
                    scanf("%d", &element);
                    insert(q, element);
                }
                break;
            case 2:
                delete(q);
                break;
            case 3:
                display(q);
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 4);
}

void palindromeCheck() {
    char str[100];
    printf("Enter a string to check for palindrome: ");
    scanf(" %[^\n]s", str);
    
    printf("\nChecking using array method...\n");
    if (isPalindromeArray(str)) {
        printf("'%s' is a palindrome (array method)\n", str);
    } else {
        printf("'%s' is not a palindrome (array method)\n", str);
    }
    
    printf("\nChecking using queue method...\n");
    if (isPalindromeQueue(str)) {
        printf("'%s' is a palindrome (queue method)\n", str);
    } else {
        printf("'%s' is not a palindrome (queue method)\n", str);
    }
}

int main() {
    int choice, capacity;
    struct Queue q;
    
    printf("Enter the capacity of the queue: ");
    scanf("%d", &capacity);
    initializeQueue(&q, capacity);
    
    do {
        printf("\nMain Menu:\n");
        printf("1. Queue Operations (Insert/Delete/Display)\n");
        printf("2. Check Palindrome\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                queueOperations(&q);
                break;
            case 2:
                palindromeCheck();
                break;
            case 3:
                printf("Exiting program...\n");
                freeQueue(&q);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 3);
    
    return 0;
}