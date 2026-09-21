#include <stdio.h>

#define MAX 100

typedef struct {
    int l, r, state;
} Node;

void merge(int a[], int l, int m, int r)
{
    int i = l, j = m + 1, k = 0;
    int temp[MAX];

    while (i <= m && j <= r)
        temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

    while (i <= m)
        temp[k++] = a[i++];

    while (j <= r)
        temp[k++] = a[j++];

    for (i = 0; i < k; i++)
        a[l + i] = temp[i];
}

void mergeSort(int a[], int n)
{
    Node stack[MAX];
    int top = -1;

    stack[++top] = (Node){0, n - 1, 0};

    while (top >= 0)
    {
        Node x = stack[top--];

        if (x.l >= x.r)
            continue;

        int m = (x.l + x.r) / 2;

        if (x.state == 0)
        {
            /* Simulate:
               mergeSort(left)
               mergeSort(right)
               merge()
            */
            stack[++top] = (Node){x.l, x.r, 1};
            stack[++top] = (Node){m + 1, x.r, 0};
            stack[++top] = (Node){x.l, m, 0};
        }
        else
        {
            merge(a, x.l, m, x.r);
        }
    }
}

int main()
{
    int a[MAX], n, i;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    mergeSort(a, n);

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);

    return 0;
}
```

