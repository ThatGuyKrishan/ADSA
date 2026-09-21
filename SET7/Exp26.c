#include <stdio.h>
#define V 4

int main() {
    int g[V][V], in[V] = {0}, q[V], f = 0, r = 0, count = 0;
    
    printf("Enter 4x4 directed adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) {
            scanf("%d", &g[i][j]);
            if (g[i][j]) in[j]++;
        }

    for (int i = 0; i < V; i++)
        if (in[i] == 0) q[r++] = i;

    printf("Topological Order: ");
    while (f < r) {
        int u = q[f++];
        printf("%d ", u);
        count++;
        for (int v = 0; v < V; v++)
            if (g[u][v] && --in[v] == 0) q[r++] = v;
    }
    
    if (count != V) printf("\nCycle detected! Topological sort not possible.");
    return 0;
}
