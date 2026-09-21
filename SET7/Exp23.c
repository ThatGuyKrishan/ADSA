#include <stdio.h>

struct Job { int id, dead, prof; };

int main() {
    int n;
    printf("Enter number of jobs: ");
    scanf("%d", &n);
    struct Job j[n];
    
    printf("Enter ID, Deadline, Profit for each job:\n");
    for (int i = 0; i < n; i++)
        scanf("%d %d %d", &j[i].id, &j[i].dead, &j[i].prof);

    // Sort jobs by profit descending (Bubble Sort)
    for (int i = 0; i < n - 1; i++)
        for (int k = 0; k < n - i - 1; k++)
            if (j[k].prof < j[k+1].prof) {
                struct Job t = j[k]; j[k] = j[k+1]; j[k+1] = t;
            }

    int maxD = 0;
    for (int i = 0; i < n; i++) if (j[i].dead > maxD) maxD = j[i].dead;

    int slot[maxD + 1], result[maxD + 1];
    for (int i = 1; i <= maxD; i++) slot[i] = 0;

    int totalProfit = 0;
    for (int i = 0; i < n; i++) {
        for (int d = j[i].dead; d > 0; d--) {
            if (slot[d] == 0) {
                slot[d] = 1;
                result[d] = j[i].id;
                totalProfit += j[i].prof;
                break;
            }
        }
    }

    printf("\nScheduled Jobs: ");
    for (int i = 1; i <= maxD; i++)
        if (slot[i]) printf("J%d ", result[i]);
    printf("\nTotal Profit: %d\n", totalProfit);
    return 0;
}
