#include <stdio.h>
#define V 4
#define INF 9999

int main() {
    int dist[V][V];
    printf("Enter adjacency matrix (use 9999 for no edge):\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            scanf("%d", &dist[i][j]);

    // Floyd-Warshall DP updates
    for (int k = 0; k < V; k++)
        for (int i = 0; i < V; i++)
            for (int j = 0; j < V; j++)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    printf("\nShortest Path Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++)
            printf("%d\t", dist[i][j]);
        printf("\n");
    }
    return 0;
}
