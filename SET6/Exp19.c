#include <stdio.h>

int n, W, maxVal = 0;
int wt[20], val[20];

void knapsack(int i, int curWt, int curVal) {
    if (curWt > W) return;
    if (curVal > maxVal) maxVal = curVal;
    if (i == n) return;

    // Include item i
    knapsack(i + 1, curWt + wt[i], curVal + val[i]);
    // Exclude item i
    knapsack(i + 1, curWt, curVal);
}

int main() {
    printf("Enter number of items and capacity: ");
    scanf("%d %d", &n, &W);
    
    printf("Enter weight and value for each item:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d", &wt[i], &val[i]);

    knapsack(0, 0, 0);
    printf("Maximum Profit: %d\n", maxVal);
    return 0;
}
