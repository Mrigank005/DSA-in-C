#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Function to display the adjacency matrix
void displayAdjMatrix(int adjMatrix[][MAX], int vertices) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to calculate in-degree and out-degree of a vertex
void calculateDegree(int adjMatrix[][MAX], int vertices, int vertex) {
    if (vertex < 0 || vertex >= vertices) {
        printf("Invalid vertex. Must be between 0 and %d.\n", vertices - 1);
        return;
    }

    int inDegree = 0, outDegree = 0;
    for (int i = 0; i < vertices; i++) {
        outDegree += adjMatrix[vertex][i];  // Row sum
        inDegree += adjMatrix[i][vertex];  // Column sum
    }

    printf("\nIn-degree of vertex %d: %d\n", vertex, inDegree);
    printf("Out-degree of vertex %d: %d\n", vertex, outDegree);
}

int main() {
    int vertices, edges;

    // Input number of vertices and edges
    printf("Enter the number of vertices (max %d): ", MAX);
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    if (edges < 0) {
        printf("Number of edges can't be negative.\n");
        return 1;
    }

    int adjMatrix[MAX][MAX] = {0};  // Initialize matrix to 0

    // Input edges
    printf("Enter each edge as a pair of vertex indices (from to):\n");
    printf("(Vertices are numbered from 0 to %d)\n", vertices - 1);

    for (int i = 0; i < edges; i++) {
        int u, v;
        printf("Edge %d: ", i + 1);
        scanf("%d %d", &u, &v);

        if (u < 0 || v < 0 || u >= vertices || v >= vertices) {
            printf("Invalid edge (%d -> %d). Skipping this edge.\n", u, v);
            i--;  // Ask again for the same edge
            continue;
        }

        // For simple graph (single edge only), use:
        adjMatrix[u][v] = 1;
    }

    // Display the adjacency matrix
    displayAdjMatrix(adjMatrix, vertices);

    // Query for degree of a vertex
    int vertex;
    printf("\nEnter the vertex number (0 to %d) to calculate degrees: ", vertices - 1);
    scanf("%d", &vertex);
    calculateDegree(adjMatrix, vertices, vertex);

    return 0;
}
