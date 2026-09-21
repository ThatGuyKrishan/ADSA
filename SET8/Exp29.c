#include <stdio.h>
#define V 5
int g[V][V], p[V], ok = 0;

void dfs(int pos) {
    if (pos == V) {
        if (g[p[pos - 1]][p[0]]) ok = 1;
        return;
    }
    for (int v = 1; v < V && !ok; v++) {
        int safe = g[p[pos - 1]][v];
        for (int i = 0; i < pos; i++) if (p[i] == v) safe = 0;
        if (safe) {
            p[pos] = v;
            dfs(pos + 1);
        }
    }
}

int main() {
    printf("Enter 5x5 adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    p[0] = 0;
    dfs(1);
    printf(ok ? "Hamiltonian Cycle exists!\n" : "No Hamiltonian Cycle found.\n");
    return 0;
}
