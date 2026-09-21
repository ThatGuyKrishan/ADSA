#include <stdio.h>
#define V 4

int parent[V];

int find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

int main() {
    int g[V][V], edges[V * V][3], eCount = 0;
    
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        for (int j = 0; j < V; j++) {
            scanf("%d", &g[i][j]);
            if (i < j && g[i][j] != 0) {
                edges[eCount][0] = i;
                edges[eCount][1] = j;
                edges[eCount][2] = g[i][j];
                eCount++;
            }
        }
    }

    // Sort edges by weight (Bubble Sort)
    for (int i = 0; i < eCount - 1; i++)
        for (int j = 0; j < eCount - i - 1; j++)
            if (edges[j][2] > edges[j + 1][2]) {
                int t0 = edges[j][0], t1 = edges[j][1], t2 = edges[j][2];
                edges[j][0] = edges[j+1][0]; edges[j][1] = edges[j+1][1]; edges[j][2] = edges[j+1][2];
                edges[j+1][0] = t0; edges[j+1][1] = t1; edges[j+1][2] = t2;
            }

    int total = 0, count = 0;
    printf("Edge \tWeight\n");
    for (int i = 0; i < eCount && count < V - 1; i++) {
        int u = find(edges[i][0]);
        int v = find(edges[i][1]);
        if (u != v) {
            parent[u] = v;
            printf("%d - %d \t%d\n", edges[i][0], edges[i][1], edges[i][2]);
            total += edges[i][2];
            count++;
        }
    }
    printf("Total Weight: %d\n", total);
    return 0;
}
