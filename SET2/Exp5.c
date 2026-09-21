```c
#include <stdio.h>

void mergeSort(int a[], int n)
{
    int temp[100], size, left, mid, right;
    int i, j, k;

    for (size = 1; size < n; size *= 2)
    {
        for (left = 0; left < n - 1; left += 2 * size)
        {
            mid = left + size;
            right = left + 2 * size;

            if (mid > n) mid = n;
            if (right > n) right = n;

            i = left;
            j = mid;
            k = left;

            while (i < mid && j < right)
                temp[k++] = (a[i] < a[j]) ? a[i++] : a[j++];

            while (i < mid)
                temp[k++] = a[i++];

            while (j < right)
                temp[k++] = a[j++];

            for (i = left; i < right; i++)
                a[i] = temp[i];
        }
    }
}

int main()
{
    int a[100], n, i;

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
