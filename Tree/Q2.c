#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Queue node for level-order insertion
struct queue_node {
    struct node* tree_node;
    struct queue_node* next;
};

// Queue structure
struct queue {
    struct queue_node* front;
    struct queue_node* rear;
};

// Function to create a new tree node
struct node* create_node(int data) {
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    if (!new_node) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    new_node->data = data;
    new_node->left = new_node->right = NULL;
    return new_node;
}

// Queue functions
struct queue* create_queue() {
    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(struct queue* q, struct node* n) {
    struct queue_node* temp = (struct queue_node*)malloc(sizeof(struct queue_node));
    temp->tree_node = n;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

struct node* dequeue(struct queue* q) {
    if (q->front == NULL) return NULL;
    struct queue_node* temp = q->front;
    struct node* tree_node = temp->tree_node;
    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return tree_node;
}

int is_empty(struct queue* q) {
    return q->front == NULL;
}

void free_queue(struct queue* q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

// Insert level-wise (first available left/right position)
struct node* insert_level_order(struct node* root, int data) {
    struct node* new_node = create_node(data);
    if (root == NULL) return new_node;

    struct queue* q = create_queue();
    enqueue(q, root);

    while (!is_empty(q)) {
        struct node* temp = dequeue(q);

        if (temp->left == NULL) {
            temp->left = new_node;
            break;
        } else {
            enqueue(q, temp->left);
        }

        if (temp->right == NULL) {
            temp->right = new_node;
            break;
        } else {
            enqueue(q, temp->right);
        }
    }

    free_queue(q);
    return root;
}

// Inorder traversal
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

// Preorder traversal
void preorder(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder traversal
void postorder(struct node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Free memory used by the tree
void free_tree(struct node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main() {
    struct node* root = NULL;
    int data = 0;

    printf("Enter your nodes (-1 to stop): ");
    while (1) {
        scanf("%d", &data);
        if (data == -1) break;
        root = insert_level_order(root, data);
    }

    printf("Tree created successfully!\n");

    printf("Inorder traversal:\n");
    inorder(root);

    printf("\nPreorder traversal:\n");
    preorder(root);

    printf("\nPostorder traversal:\n");
    postorder(root);

    // Free memory
    free_tree(root);
    return 0;
}
