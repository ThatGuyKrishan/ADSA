#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left,*right;
};

struct Node* newNode(int x)
{
    struct Node *p=malloc(sizeof(struct Node));
    p->data=x; p->left=p->right=NULL;
    return p;
}

void preorder(struct Node *root)
{
    struct Node *s[20],*p;
    int top=-1;

    if(!root) return;
    s[++top]=root;

    while(top!=-1) {
        p=s[top--];
        printf("%d ",p->data);

        if(p->right) s[++top]=p->right;
        if(p->left) s[++top]=p->left;
    }
}

int main()
{
    struct Node *root;
    root=newNode(1);
    root->left=newNode(2);
    root->right=newNode(3);
    root->left->left=newNode(4);
    root->left->right=newNode(5);

    printf("Preorder: ");
    preorder(root);

    return 0;
}
