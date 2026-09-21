#include <stdio.h>
#define V 4

int g[V][V], color[V], m;

int isSafe(int u, int c) {
    for (int i = 0; i < V; i++)
        if (g[u][i] && color[i] == c) return 0;
    return 1;
}

int solve(int u) {
    if (u == V) return 1;
    for (int c = 1; c <= m; c++) {
        if (isSafe(u, c)) {
            color[u] = c;
            if (solve(u + 1)) return 1;
            color[u] = 0;
        }
    }
    return 0;
}

int main() {
    printf("Enter 4x4 adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    printf("Enter number of colors: ");
    scanf("%d", &m);

    for (int i = 0; i < V; i++) color[i] = 0;

    if (solve(0)) {
        printf("Solution Exists. Assigned Colors:\n");
        for (int i = 0; i < V; i++) printf("Vertex %d -> Color %d\n", i, color[i]);
    } else {
        printf("No solution exists with %d colors.\n", m);
    }
    return 0;
}
