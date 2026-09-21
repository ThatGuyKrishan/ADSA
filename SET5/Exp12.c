#include <stdio.h>
#define V 5
#define INF 9999

int main() {
    int g[V][V], key[V], parent[V], vis[V] = {0};
    
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    for (int i = 0; i < V; i++) key[i] = INF;
    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = -1, min = INF;
        for (int v = 0; v < V; v++)
            if (!vis[v] && key[v] < min) { min = key[v]; u = v; }

        vis[u] = 1;

        for (int v = 0; v < V; v++)
            if (g[u][v] && !vis[v] && g[u][v] < key[v]) {
                parent[v] = u;
                key[v] = g[u][v];
            }
    }

    int total = 0;
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, g[i][parent[i]]);
        total += key[i];
    }
    printf("Total Weight: %d\n", total);
    return 0;
}
