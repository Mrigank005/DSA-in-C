#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5

// Circular Queue structure
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} CircularQueue;

// Initialize the circular queue
void initializeQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is empty
bool isEmpty(CircularQueue *q) {
    return (q->front == -1 && q->rear == -1);
}

// Check if the queue is full
bool isFull(CircularQueue *q) {
    return ((q->rear + 1) % MAX_SIZE == q->front);
}

// Insert an element into the circular queue (enqueue)
void insert(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot insert %d\n", value);
        return;
    }
    
    if (isEmpty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear = (q->rear + 1) % MAX_SIZE;
    }
    
    q->items[q->rear] = value;
    printf("Inserted %d into the queue\n", value);
}

// Delete an element from the circular queue (dequeue)
int delete(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot delete\n");
        return -1;
    }
    
    int deletedValue = q->items[q->front];
    
    if (q->front == q->rear) {
        // Queue has only one element, reset after deletion
        q->front = q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    
    printf("Deleted %d from the queue\n", deletedValue);
    return deletedValue;
}

// Display the circular queue
void display(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    printf("Circular Queue elements: ");
    int i = q->front;
    
    do {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX_SIZE;
    } while (i != (q->rear + 1) % MAX_SIZE);
    
    printf("\n");
}

// Main function with menu-driven interface
int main() {
    CircularQueue q;
    initializeQueue(&q);
    int choice, value;
    
    while (1) {
        printf("\nCircular Queue Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insert(&q, value);
                break;
            case 2:
                delete(&q);
                break;
            case 3:
                display(&q);
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