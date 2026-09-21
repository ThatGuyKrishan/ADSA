#include <stdio.h>

#define MAX 100

void print(int a[], int n) {
    for(int i=0;i<n;i++)
        printf("%d ",a[i]);
    printf("\n");
}

/* 1. Insertion Sort */
void insertion(int a[], int n) {
    int i,j,key;
    for(i=1;i<n;i++) {
        key=a[i];
        j=i-1;
        while(j>=0 && a[j]>key) {
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
}

/* 2. Bubble Sort */
void bubble(int a[], int n) {
    int i,j,t;
    for(i=0;i<n-1;i++)
        for(j=0;j<n-i-1;j++)
            if(a[j]>a[j+1]) {
                t=a[j]; a[j]=a[j+1]; a[j+1]=t;
            }
}

/* 3. Selection Sort */
void selection(int a[], int n) {
    int i,j,min,t;
    for(i=0;i<n-1;i++) {
        min=i;
        for(j=i+1;j<n;j++)
            if(a[j]<a[min])
                min=j;

        t=a[i]; a[i]=a[min]; a[min]=t;
    }
}

/* 4. Shell Sort */
void shell(int a[], int n) {
    int gap,i,j,temp;
    for(gap=n/2;gap>0;gap/=2)
        for(i=gap;i<n;i++) {
            temp=a[i];
            for(j=i;j>=gap && a[j-gap]>temp;j-=gap)
                a[j]=a[j-gap];
            a[j]=temp;
        }
}

/* 5. Quick Sort - Iterative */
void quick(int a[], int n) {
    int stack[MAX],top=-1,l,r,i,j,p,t;

    stack[++top]=0;
    stack[++top]=n-1;

    while(top>=0) {
        r=stack[top--];
        l=stack[top--];

        i=l; j=r;
        p=a[(l+r)/2];

        while(i<=j) {
            while(a[i]<p) i++;
            while(a[j]>p) j--;

            if(i<=j) {
                t=a[i]; a[i]=a[j]; a[j]=t;
                i++; j--;
            }
        }

        if(l<j) {
            stack[++top]=l;
            stack[++top]=j;
        }

        if(i<r) {
            stack[++top]=i;
            stack[++top]=r;
        }
    }
}

/* 6. Merge Sort - Iterative */
void mergeSort(int a[], int n) {
    int b[MAX],size,left,mid,right,i,j,k;

    for(size=1;size<n;size*=2) {
        for(left=0;left<n;left+=2*size) {
            mid=left+size;
            right=left+2*size;

            if(mid>n) mid=n;
            if(right>n) right=n;

            i=left; j=mid; k=left;

            while(i<mid && j<right)
                b[k++]=(a[i]<a[j])?a[i++]:a[j++];

            while(i<mid) b[k++]=a[i++];
            while(j<right) b[k++]=a[j++];
        }

        for(i=0;i<n;i++)
            a[i]=b[i];
    }
}

/* 7. Heap Sort */
void heap(int a[], int n) {
    int i,j,t;

    for(i=n/2-1;i>=0;i--) {
        j=i;
        while(2*j+1<n) {
            int c=2*j+1;

            if(c+1<n && a[c+1]>a[c])
                c++;

            if(a[j]>=a[c])
                break;

            t=a[j]; a[j]=a[c]; a[c]=t;
            j=c;
        }
    }

    for(i=n-1;i>0;i--) {
        t=a[0]; a[0]=a[i]; a[i]=t;

        j=0;
        while(2*j+1<i) {
            int c=2*j+1;

            if(c+1<i && a[c+1]>a[c])
                c++;

            if(a[j]>=a[c])
                break;

            t=a[j]; a[j]=a[c]; a[c]=t;
            j=c;
        }
    }
}

/* 8. Radix Sort */
void radix(int a[], int n) {
    int b[MAX],exp,max=a[0],i,c[10];

    for(i=1;i<n;i++)
        if(a[i]>max) max=a[i];

    for(exp=1;max/exp>0;exp*=10) {
        for(i=0;i<10;i++)
            c[i]=0;

        for(i=0;i<n;i++)
            c[(a[i]/exp)%10]++;

        for(i=1;i<10;i++)
            c[i]+=c[i-1];

        for(i=n-1;i>=0;i--)
            b[--c[(a[i]/exp)%10]]=a[i];

        for(i=0;i<n;i++)
            a[i]=b[i];
    }
}

/* 9. Counting Sort */
void counting(int a[], int n) {
    int count[MAX]={0},max=a[0],i,k=0;

    for(i=1;i<n;i++)
        if(a[i]>max) max=a[i];

    for(i=0;i<n;i++)
        count[a[i]]++;

    for(i=0;i<=max;i++)
        while(count[i]--)
            a[k++]=i;
}

/* 10. Bucket Sort */
void bucket(int a[], int n) {
    int b[MAX]={0},max=a[0],i,k=0;

    for(i=1;i<n;i++)
        if(a[i]>max) max=a[i];

    for(i=0;i<n;i++)
        b[a[i]]++;

    for(i=0;i<=max;i++)
        while(b[i]--)
            a[k++]=i;
}

/* 11. Radix Exchange Sort - Iterative */
void radixExchange(int a[], int n) {
    int stack[MAX],top=-1;
    int l,r,bit,max=a[0],i,j,t;

    for(i=1;i<n;i++)
        if(a[i]>max) max=a[i];

    bit=0;
    while((1<<bit)<=max)
        bit++;

    stack[++top]=0;
    stack[++top]=n-1;
    stack[++top]=bit-1;

    while(top>=0) {
        bit=stack[top--];
        r=stack[top--];
        l=stack[top--];

        if(l>=r || bit<0)
            continue;

        i=l; j=r;

        while(i<=j) {
            while(i<=r && !(a[i]&(1<<bit))) i++;
            while(j>=l && (a[j]&(1<<bit))) j--;

            if(i<j) {
                t=a[i]; a[i]=a[j]; a[j]=t;
                i++; j--;
            }
        }

        if(l<j) {
            stack[++top]=l;
            stack[++top]=j;
            stack[++top]=bit-1;
        }

        if(i<r) {
            stack[++top]=i;
            stack[++top]=r;
            stack[++top]=bit-1;
        }
    }
}

/* 12. Address Calculation Sort */
void addressSort(int a[], int n) {
    int address[MAX]={0};
    int i,k=0,max=a[0];

    for(i=1;i<n;i++)
        if(a[i]>max) max=a[i];

    for(i=0;i<n;i++)
        address[a[i]]++;

    for(i=0;i<=max;i++)
        while(address[i]--)
            a[k++]=i;
}

int main(void) {
    int a[MAX],n,choice,i;
    
    printf("Enter number of elements: ");
    scanf("%d",&n);
    
    printf("Enter elements: ");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    
    printf("\n--- SORTING MENU ---\n");
    printf("1. Insertion Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Shell Sort\n");
    printf("5. Quick Sort\n");
    printf("6. Merge Sort\n");
    printf("7. Heap Sort\n");
    printf("8. Radix Sort\n");
    printf("9. Counting Sort\n");
    printf("10. Bucket Sort\n");
    printf("11. Radix Exchange Sort\n");
    printf("12. Address Calculation Sort\n");
    
    printf("Enter choice: ");
    scanf("%d",&choice);
    
    switch(choice) {
        case 1: insertion(a,n); break;
        case 2: bubble(a,n); break;
        case 3: selection(a,n); break;
        case 4: shell(a,n); break;
        case 5: quick(a,n); break;
        case 6: mergeSort(a,n); break;
        case 7: heap(a,n); break;
        case 8: radix(a,n); break;
        case 9: counting(a,n); break;
        case 10: bucket(a,n); break;
        case 11: radixExchange(a,n); break;
        case 12: addressSort(a,n); break;
        default:
            printf("Invalid choice");
            return 0;
    }
    
    printf("\nSorted array: ");
    print(a,n);
    
    return 0;
}

