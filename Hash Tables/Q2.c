#include <stdio.h>
#include <stdlib.h>

// Define the structure of a node
typedef struct Node {
    int value;
    struct Node *next;
} Node;

// Hash function
int hashFunction(int key, int tableSize) {
    return key % tableSize;
}

// Initialize hash table
void initializeHashTable(Node *hashTable[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        hashTable[i] = NULL;
    }
}

// Insert value into hash table
void insertValue(Node *hashTable[], int tableSize, int value) {
    int index = hashFunction(value, tableSize);
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->value = value;
    newNode->next = hashTable[index];
    hashTable[index] = newNode;
}

// Search value in hash table
Node *searchValue(Node *hashTable[], int tableSize, int value) {
    int index = hashFunction(value, tableSize);
    Node *current = hashTable[index];
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Delete value from hash table
void deleteValue(Node *hashTable[], int tableSize, int value) {
    int index = hashFunction(value, tableSize);
    Node *current = hashTable[index];
    Node *previous = NULL;

    while (current != NULL && current->value != value) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Value not found in the hash table.\n");
        return;
    }

    if (previous == NULL) {
        hashTable[index] = current->next;
    } else {
        previous->next = current->next;
    }

    free(current);
    printf("Value deleted successfully.\n");
}

// Display hash table
void displayHashTable(Node *hashTable[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        printf("Bucket %d: ", i);
        Node *current = hashTable[i];
        while (current != NULL) {
            printf("%d -> ", current->value);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Free all memory used by the hash table
void freeHashTable(Node *hashTable[], int tableSize) {
    for (int i = 0; i < tableSize; i++) {
        Node *current = hashTable[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int tableSize, choice, value;

    printf("Enter the size of the hash table: ");
    scanf("%d", &tableSize);
    if (tableSize <= 0) {
        printf("Invalid table size.\n");
        return 1;
    }

    Node *hashTable[tableSize];
    initializeHashTable(hashTable, tableSize);

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Insert a value\n");
        printf("2. Search for a value\n");
        printf("3. Delete a value\n");
        printf("4. Display the hash table\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to insert: ");
                scanf("%d", &value);
                insertValue(hashTable, tableSize, value);
                break;
            case 2:
                printf("Enter the value to search: ");
                scanf("%d", &value);
                if (searchValue(hashTable, tableSize, value)) {
                    printf("Value found in the hash table.\n");
                } else {
                    printf("Value not found in the hash table.\n");
                }
                break;
            case 3:
                printf("Enter the value to delete: ");
                scanf("%d", &value);
                deleteValue(hashTable, tableSize, value);
                break;
            case 4:
                displayHashTable(hashTable, tableSize);
                break;
            case 5:
                freeHashTable(hashTable, tableSize);
                printf("Exiting... All memory freed.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
