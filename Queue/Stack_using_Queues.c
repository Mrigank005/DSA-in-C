#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Queue structure
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// Stack structure using two queues
typedef struct {
    Queue q1;
    Queue q2;
} Stack;

// Initialize a queue
void initializeQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if queue is empty
bool isQueueEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Check if queue is full
bool isQueueFull(Queue *q) {
    return (q->rear == MAX_SIZE - 1);
}

// Enqueue operation
void enqueue(Queue *q, int value) {
    if (isQueueFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isQueueEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->items[q->rear] = value;
}

// Dequeue operation
int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->items[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return item;
}

// Initialize stack
void initializeStack(Stack *s) {
    initializeQueue(&s->q1);
    initializeQueue(&s->q2);
}

// Push operation for stack (costly operation)
void push(Stack *s, int value) {
    // Move all elements from q1 to q2
    while (!isQueueEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }
    
    // Enqueue the new element to q1
    enqueue(&s->q1, value);
    
    // Move all elements back from q2 to q1
    while (!isQueueEmpty(&s->q2)) {
        enqueue(&s->q1, dequeue(&s->q2));
    }
    
    printf("Pushed %d to stack\n", value);
}

// Pop operation for stack
int pop(Stack *s) {
    if (isQueueEmpty(&s->q1)) {
        printf("Stack is empty\n");
        return -1;
    }
    int item = dequeue(&s->q1);
    printf("Popped %d from stack\n", item);
    return item;
}

// Display stack contents
void displayStack(Stack *s) {
    if (isQueueEmpty(&s->q1)) {
        printf("Stack is empty\n");
        return;
    }
    
    printf("Stack elements: ");
    for (int i = s->q1.front; i <= s->q1.rear; i++) {
        printf("%d ", s->q1.items[i]);
    }
    printf("\n");
}

int main() {
    Stack s;
    initializeStack(&s);
    int choice, value;
    
    while (1) {
        printf("\nStack Operations (using queues):\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to push: ");
                scanf("%d", &value);
                push(&s, value);
                break;
            case 2:
                pop(&s);
                break;
            case 3:
                displayStack(&s);
                break;
            case 4:
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    
    return 0;
}