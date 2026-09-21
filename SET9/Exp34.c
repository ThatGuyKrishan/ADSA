#include <stdio.h>
struct Pt { int x, y; };

int main() {
    int n;
    printf("Enter number of points and their coordinates (x y):\n");
    scanf("%d", &n);
    struct Pt pt[n];
    for (int i = 0; i < n; i++) scanf("%d %d", &pt[i].x, &pt[i].y);

    int l = 0;
    for (int i = 1; i < n; i++) if (pt[i].x < pt[l].x) l = i;

    int p = l, q;
    printf("Convex Hull Boundary Points:\n");
    do {
        printf("(%d, %d)\n", pt[p].x, pt[p].y);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
            if ((pt[i].x - pt[p].x) * (pt[q].y - pt[p].y) - (pt[i].y - pt[p].y) * (pt[q].x - pt[p].x) > 0)
                q = i;
        p = q;
    } while (p != l);
    return 0;
}
