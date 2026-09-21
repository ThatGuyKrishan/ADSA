#include <stdio.h>
#define V 4

int g[V][V], disc[V], vis[V], t = 0;

void dfs(int u) {
    disc[u] = ++t;
    vis[u] = 1; // 1 = visiting (recursion stack)

    for (int v = 0; v < V; v++) {
        if (g[u][v]) {
            if (!disc[v]) {
                printf("Tree Edge: %d -> %d\n", u, v);
                dfs(v);
            } else if (vis[v] == 1) {
                printf("Back Edge: %d -> %d\n", u, v);
            } else {
                if (disc[u] < disc[v])
                    printf("Forward Edge: %d -> %d\n", u, v);
                else
                    printf("Cross Edge: %d -> %d\n", u, v);
            }
        }
    }
    vis[u] = 2; // 2 = fully visited/finished
}

int main() {
    printf("Enter 4x4 directed adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    for (int i = 0; i < V; i++) {
        disc[i] = 0;
        vis[i] = 0;
    }

    printf("\nEdge Classifications:\n");
    for (int i = 0; i < V; i++)
        if (!disc[i]) dfs(i);

    return 0;
}
