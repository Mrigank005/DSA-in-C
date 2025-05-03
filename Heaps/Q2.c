#include <stdio.h>
#define MAX_SIZE 100

// Function to heapify the subtree rooted at index 'i'
void heapify(int heap[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right <= n && heap[right] > heap[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        heapify(heap, n, largest);
    }
}

// Function to build a max-heap from an unordered array
void buildMaxHeap(int heap[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        heapify(heap, n, i);
    }
}

// Function to insert a value into the max-heap
void insertMaxHeap(int heap[], int *n, int val) {
    if (*n >= MAX_SIZE - 1) {
        printf("Heap is full. Cannot insert more elements.\n");
        return;
    }

    *n = *n + 1;
    int pos = *n;
    heap[pos] = val;

    while (pos > 1 && heap[pos] > heap[pos / 2]) {
        int temp = heap[pos];
        heap[pos] = heap[pos / 2];
        heap[pos / 2] = temp;
        pos = pos / 2;
    }
}

// Function to delete the root of the max-heap
void deleteMaxHeap(int heap[], int *n) {
    if (*n == 0) {
        printf("Heap is empty. Cannot delete.\n");
        return;
    }

    printf("Deleted root: %d\n", heap[1]);
    heap[1] = heap[*n];
    (*n)--;
    heapify(heap, *n, 1);
}

// Function to print the heap
void printHeap(int heap[], int n) {
    if (n == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Heap elements:\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", heap[i]);
    }
    printf("\n");
}

int main() {
    int heap[MAX_SIZE];
    int n, choice, val;

    printf("Enter the initial number of elements in the heap: ");
    scanf("%d", &n);

    if (n < 0 || n >= MAX_SIZE) {
        printf("Invalid size. Must be between 0 and %d.\n", MAX_SIZE - 1);
        return 1;
    }

    printf("Enter the elements:\n");
    for (int i = 1; i <= n; i++) {
        scanf("%d", &heap[i]);
    }

    buildMaxHeap(heap, n);

    while (1) {
        printf("\n--- Max-Heap Operations ---\n");
        printf("1. Insert a value\n");
        printf("2. Delete the root\n");
        printf("3. Print the heap\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &val);
                insertMaxHeap(heap, &n, val);
                break;
            case 2:
                deleteMaxHeap(heap, &n);
                break;
            case 3:
                printHeap(heap, n);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
