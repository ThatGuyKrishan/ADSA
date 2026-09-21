#include <stdio.h>
#define V 4

int main() {
    int g[V][V], color[V], q[V], f = 0, r = 0, bipartite = 1;
    printf("Enter %dx%d adjacency matrix:\n", V, V);
    for (int i = 0; i < V; i++) {
        color[i] = -1;
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);
    }

    color[0] = 0;
    q[r++] = 0;

    while (f < r && bipartite) {
        int u = q[f++];
        for (int v = 0; v < V; v++) {
            if (g[u][v] && color[v] == -1) {
                color[v] = 1 - color[u];
                q[r++] = v;
            } else if (g[u][v] && color[v] == color[u]) {
                bipartite = 0;
                break;
            }
        }
    }

    printf(bipartite ? "Graph is Bipartite (2-colorable).\n" : "Graph is NOT Bipartite.\n");
    return 0;
}
