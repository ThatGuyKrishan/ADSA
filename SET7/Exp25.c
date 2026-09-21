#include <stdio.h>
#define V 5

int g[V][V], disc[V], low[V], stack[V], inStack[V], top = -1, t = 0;

void dfs(int u, int p) {
    disc[u] = low[u] = ++t;
    stack[++top] = u;
    inStack[u] = 1;
    int children = 0, isAP = 0;

    for (int v = 0; v < V; v++) {
        if (g[u][v]) {
            if (v == p) continue;
            if (disc[v]) {
                if (inStack[v] && disc[v] < low[u]) low[u] = disc[v];
            } else {
                children++;
                dfs(v, u);
                if (low[v] < low[u]) low[u] = low[v];
                
                // Bridge Condition
                if (low[v] > disc[u]) printf("Bridge: %d - %d\n", u, v);
                
                // Articulation Point Condition
                if (p != -1 && low[v] >= disc[u]) isAP = 1;
            }
        }
    }
    if (p == -1 && children > 1) isAP = 1;
    if (isAP) printf("Articulation Point: %d\n", u);

    // SCC extraction
    if (low[u] == disc[u]) {
        printf("SCC: ");
        while (1) {
            int v = stack[top--];
            inStack[v] = 0;
            printf("%d ", v);
            if (u == v) break;
        }
        printf("\n");
    }
}

int main() {
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    printf("\nGraph Analysis Results:\n");
    for (int i = 0; i < V; i++)
        if (!disc[i]) dfs(i, -1);

    return 0;
}
