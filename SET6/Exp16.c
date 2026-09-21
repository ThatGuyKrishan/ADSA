#include <stdio.h>
#define INF 9999

int main() {
    int V, E, src;
    printf("Enter vertices and edges: ");
    scanf("%d %d", &V, &E);
    
    int edges[E][3], dist[V];
    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < E; i++)
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    // Relax all edges V - 1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j][0], v = edges[j][1], w = edges[j][2];
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycle
    for (int j = 0; j < E; j++) {
        int u = edges[j][0], v = edges[j][1], w = edges[j][2];
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected!\n");
            return 0;
        }
    }

    printf("Vertex\tDistance\n");
    for (int i = 0; i < V; i++)
        printf("%d\t%d\n", i, dist[i]);

    return 0;
}
