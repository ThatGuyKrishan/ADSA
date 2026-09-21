#include <stdio.h>
#include <string.h>
#define MAX 256

void badChar(char *p, int m, int bc[MAX]) {
    for (int i = 0; i < MAX; i++) bc[i] = -1;
    for (int i = 0; i < m; i++) bc[(int)p[i]] = i;
}

int main() {
    char t[100], p[100];
    printf("Enter text and pattern:\n");
    scanf("%s %s", t, p);
    
    int n = strlen(t), m = strlen(p), bc[MAX];
    badChar(p, m, bc);
    
    int s = 0;
    while (s <= n - m) {
        int j = m - 1;
        while (j >= 0 && p[j] == t[s + j]) j--;
        if (j < 0) {
            printf("Pattern found at index %d\n", s);
            s += (s + m < n) ? m - bc[(int)t[s + m]] : 1;
        } else {
            int shift = j - bc[(int)t[s + j]];
            s += (shift > 0) ? shift : 1;
        }
    }
    return 0;
}
