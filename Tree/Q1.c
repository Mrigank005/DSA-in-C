#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define EMPTY -1  // Sentinel value to mark unused slots

// Function to insert a value at a specific index
void insert(int tree[], int index, int value, int size) {
    if (index >= size) {
        printf("Error: Index out of bounds\n");
        return;
    }
    tree[index] = value;
}

// Function to get the left child of a node
int get_left_child(int tree[], int index, int size) {
    int left_index = 2 * index + 1;
    if (left_index < size && tree[left_index] != EMPTY) {
        return tree[left_index];
    } else {
        return EMPTY;
    }
}

// Function to get the right child of a node
int get_right_child(int tree[], int index, int size) {
    int right_index = 2 * index + 2;
    if (right_index < size && tree[right_index] != EMPTY) {
        return tree[right_index];
    } else {
        return EMPTY;
    }
}

// Function to display the binary tree as an array
void display(int tree[], int size) {
    printf("Binary Tree as Array:\n");
    for (int i = 0; i < size; i++) {
        if (tree[i] != EMPTY)
            printf("%d ", tree[i]);
        else
            printf("_ ");  // Display placeholder for empty nodes
    }
    printf("\n");
}

int main() {
    int tree[MAX_SIZE];
    int n, value;

    // Initialize the tree array with EMPTY (-1)
    for (int i = 0; i < MAX_SIZE; i++) {
        tree[i] = EMPTY;
    }

    // Input number of nodes
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    if (n > MAX_SIZE) {
        printf("Error: Maximum allowed nodes is %d\n", MAX_SIZE);
        return 1;
    }

    // Input node values
    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        printf("Node %d: ", i);
        scanf("%d", &value);
        insert(tree, i, value, n);
    }

    // Display the tree
    display(tree, n);

    // Display left and right children of the root (index 0)
    int left = get_left_child(tree, 0, n);
    int right = get_right_child(tree, 0, n);

    if (left != EMPTY) {
        printf("Left child of root: %d\n", left);
    } else {
        printf("Root has no left child.\n");
    }

    if (right != EMPTY) {
        printf("Right child of root: %d\n", right);
    } else {
        printf("Root has no right child.\n");
    }

    return 0;
}
