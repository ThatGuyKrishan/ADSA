#include <stdio.h>
#define N 20

int q1[N],q2[N],f1=0,r1=0,f2=0,r2=0;

void push(int x)
{
    q1[r1++]=x;
}

int pop()
{
    int x;
    if(f1==r1) return -1;

    while(f1<r1-1)
        q2[r2++]=q1[f1++];

    x=q1[f1++];
    f1=r1=0;

    while(f2<r2) q1[r1++]=q2[f2++];
    f2=r2=0;

    return x;
}

int main()
{
    int n,x,i;
    printf("Enter number of elements: ");
    scanf("%d",&n);

    printf("Enter elements: ");
    for(i=0;i<n;i++) {
        scanf("%d",&x);
        push(x);
    }

    printf("Popped: %d\n",pop());
    printf("Popped: %d\n",pop());

    return 0;
}
