#include <stdio.h>
#define V 5
#define INF 99
int g[V][V], maxC = 0, vis[V];

void dfs(int u, int s, int d) {
    vis[u] = 1;
    for (int v = 0; v < V; v++)
        if (g[u][v]) {
            if (v == s && d >= 2 && d + 1 > maxC) maxC = d + 1;
            else if (!vis[v]) dfs(v, s, d + 1);
        }
    vis[u] = 0;
}

int main() {
    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) scanf("%d", &g[i][j]);

    int minC = INF;
    for (int i = 0; i < V; i++) {
        int dist[V], par[V], q[V], f = 0, r = 0;
        for (int j = 0; j < V; j++) { dist[j] = INF; par[j] = -1; }
        dist[i] = 0; q[r++] = i;
        
        while (f < r) {
            int u = q[f++];
            for (int v = 0; v < V; v++)
                if (g[u][v]) {
                    if (dist[v] == INF) { dist[v] = dist[u] + 1; par[v] = u; q[r++] = v; }
                    else if (par[u] != v) { int l = dist[u] + dist[v] + 1; if (l < minC) minC = l; }
                }
        }
        dfs(i, i, 0);
    }
    printf("Smallest Cycle: %d\nLargest Cycle: %d\n", minC == INF ? 0 : minC, maxC);
    return 0;
}
