#include <stdio.h>

int main() {
    int n, amt;
    printf("Enter number of coin types: ");
    scanf("%d", &n);
    
    int c[n];
    printf("Enter coins (sorted descending):\n");
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    printf("Enter target amount: ");
    scanf("%d", &amt);

    printf("Coin breakdown:\n");
    for (int i = 0; i < n; i++) {
        if (amt >= c[i]) {
            int count = amt / c[i];
            amt %= c[i];
            printf("%d x %d\n", c[i], count);
        }
    }
    return 0;
}

