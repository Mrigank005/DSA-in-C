#include <stdio.h>

// Function to check if the graph is undirected
void checkIfUndirected(int adjMatrix[][100], int vertices) {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            // If the edge from i to j is not equal to the edge from j to i, the graph is directed
            if (adjMatrix[i][j] != adjMatrix[j][i]) {
                printf("Graph is not undirected.\n");
                return;
            }
        }
    }
    printf("Graph is undirected.\n");
}

int main() {
    int vertices, edges;

    // Input number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > 100) {
        printf("Invalid number of vertices. Please enter a value between 1 and 100.\n");
        return 1;
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    if (edges < 0) {
        printf("Number of edges can't be negative.\n");
        return 1;
    }

    int adjMatrix[100][100] = {0};  // Initialize adjacency matrix to 0

    // Input the edges (directed edges)
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

        adjMatrix[u][v] = 1;  // Set the edge
    }

    // Check if the graph is undirected
    checkIfUndirected(adjMatrix, vertices);

    return 0;
}
