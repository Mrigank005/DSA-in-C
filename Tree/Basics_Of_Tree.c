#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
}; 

struct Node* createNode(int val) {
    struct Node* node 
              = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void inorderTraversal(struct Node* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

void preorderTraversal(struct Node* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void postorderTraversal(struct Node* node) {
    if (node == NULL) return;
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->data);
}

struct Node* buildTree() {
    int data;
    printf("Enter data for the node (or -1 to skip): ");
    scanf("%d", &data);

    if (data == -1) {
        return NULL;
    }

    struct Node* node = createNode(data);

    printf("Enter left child of %d:\n", data);
    node->left = buildTree();

    printf("Enter right child of %d:\n", data);
    node->right = buildTree();

    return node;
}

void bfsTraversal(struct Node* root) {
    if (root == NULL) return;

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* currentNode = queue[front++];

        printf("%d ", currentNode->data);

        if (currentNode->left != NULL) {
            queue[rear++] = currentNode->left;
        }

        if (currentNode->right != NULL) {
            queue[rear++] = currentNode->right;
        }
    }
}

int main() {

    printf("Construct the binary tree:\n");
    struct Node* root = buildTree();

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");
    
    printf("BFS traversal: ");
    bfsTraversal(root);
    printf("\n");

    return 0;
}
