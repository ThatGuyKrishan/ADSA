#include <stdio.h>

int n, m, g[20][20], path[20], found = 0;

int isClique(int size) {
    for (int i = 0; i < size; i++)
        for (int j = i + 1; j < size; j++)
            if (!g[path[i]][path[j]]) return 0;
    return 1;
}

void findClique(int idx, int start) {
    if (idx == m) {
        if (isClique(m)) found = 1;
        return;
    }
    for (int i = start; i < n && !found; i++) {
        path[idx] = i;
        findClique(idx + 1, i + 1);
    }
}

int main() {
    printf("Enter number of vertices (n) and clique size (m): ");
    scanf("%d %d", &n, &m);
    
    printf("Enter %dx%d adjacency matrix:\n", n, n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) scanf("%d", &g[i][j]);

    findClique(0, 0);
    if (found) printf("Result: Clique of size %d exists!\n", m);
    else printf("Result: No clique of size %d found.\n", m);
    return 0;
}
