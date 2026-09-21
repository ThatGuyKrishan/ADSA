#include <stdio.h>
#include <stdlib.h>

/* =========================================================
                     1. AVL TREE
   ========================================================= */

typedef struct AVL {
    int key, h;
    struct AVL *left, *right;
} AVL;

int ah(AVL *p)
{
    return p ? p->h : 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

AVL *createTreeAVL(int x)
{
    AVL *p = malloc(sizeof(AVL));
    p->key = x;
    p->h = 1;
    p->left = p->right = NULL;
    return p;
}

AVL *rightRotate(AVL *y)
{
    AVL *x = y->left;
    AVL *t = x->right;

    x->right = y;
    y->left = t;

    y->h = 1 + max(ah(y->left), ah(y->right));
    x->h = 1 + max(ah(x->left), ah(x->right));

    return x;
}

AVL *leftRotate(AVL *x)
{
    AVL *y = x->right;
    AVL *t = y->left;

    y->left = x;
    x->right = t;

    x->h = 1 + max(ah(x->left), ah(x->right));
    y->h = 1 + max(ah(y->left), ah(y->right));

    return y;
}

AVL *insertItemAVL(AVL *p, int x)
{
    int b;

    if (!p)
        return createTreeAVL(x);

    if (x < p->key)
        p->left = insertItemAVL(p->left, x);
    else if (x > p->key)
        p->right = insertItemAVL(p->right, x);
    else
        return p;

    p->h = 1 + max(ah(p->left), ah(p->right));
    b = ah(p->left) - ah(p->right);

    if (b > 1 && x < p->left->key)
        return rightRotate(p);

    if (b < -1 && x > p->right->key)
        return leftRotate(p);

    if (b > 1 && x > p->left->key) {
        p->left = leftRotate(p->left);
        return rightRotate(p);
    }

    if (b < -1 && x < p->right->key) {
        p->right = rightRotate(p->right);
        return leftRotate(p);
    }

    return p;
}

AVL *minAVL(AVL *p)
{
    while (p->left)
        p = p->left;
    return p;
}

AVL *deleteItemAVL(AVL *p, int x)
{
    int b;

    if (!p)
        return NULL;

    if (x < p->key)
        p->left = deleteItemAVL(p->left, x);
    else if (x > p->key)
        p->right = deleteItemAVL(p->right, x);
    else {
        if (!p->left || !p->right) {
            AVL *t = p->left ? p->left : p->right;

            if (!t) {
                free(p);
                return NULL;
            }

            *p = *t;
            free(t);
        } else {
            AVL *t = minAVL(p->right);
            p->key = t->key;
            p->right = deleteItemAVL(p->right, t->key);
        }
    }

    p->h = 1 + max(ah(p->left), ah(p->right));
    b = ah(p->left) - ah(p->right);

    if (b > 1 && ah(p->left->left) >= ah(p->left->right))
        return rightRotate(p);

    if (b > 1) {
        p->left = leftRotate(p->left);
        return rightRotate(p);
    }

    if (b < -1 && ah(p->right->right) >= ah(p->right->left))
        return leftRotate(p);

    if (b < -1) {
        p->right = rightRotate(p->right);
        return leftRotate(p);
    }

    return p;
}

AVL *searchItemAVL(AVL *p, int x)
{
    if (!p || p->key == x)
        return p;

    if (x < p->key)
        return searchItemAVL(p->left, x);

    return searchItemAVL(p->right, x);
}

void deleteTreeAVL(AVL *p)
{
    if (p) {
        deleteTreeAVL(p->left);
        deleteTreeAVL(p->right);
        free(p);
    }
}

void printAVL(AVL *p)
{
    if (p) {
        printAVL(p->left);
        printf("%d ", p->key);
        printAVL(p->right);
    }
}


/* =========================================================
                   2. RED-BLACK TREE
   ========================================================= */

#define RED 1
#define BLACK 0

typedef struct RB {
    int key, color;
    struct RB *left, *right, *parent;
} RB;

RB *NIL;

void initRB()
{
    NIL = malloc(sizeof(RB));
    NIL->color = BLACK;
    NIL->left = NIL->right = NIL->parent = NIL;
}

RB *createTreeRB(int x)
{
    RB *p = malloc(sizeof(RB));

    p->key = x;
    p->color = RED;
    p->left = p->right = p->parent = NIL;

    return p;
}

void rbLeftRotate(RB **root, RB *x)
{
    RB *y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rbRightRotate(RB **root, RB *y)
{
    RB *x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

void rbInsertFix(RB **root, RB *z)
{
    RB *y;

    while (z->parent->color == RED) {

        if (z->parent == z->parent->parent->left) {

            y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rbLeftRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbRightRotate(root, z->parent->parent);
            }
        }

        else {

            y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rbRightRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rbLeftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

void insertItemRB(RB **root, int x)
{
    RB *z = createTreeRB(x);
    RB *y = NIL;
    RB *p = *root;

    while (p != NIL) {
        y = p;

        if (x < p->key)
            p = p->left;
        else if (x > p->key)
            p = p->right;
        else {
            free(z);
            return;
        }
    }

    z->parent = y;

    if (y == NIL)
        *root = z;
    else if (x < y->key)
        y->left = z;
    else
        y->right = z;

    rbInsertFix(root, z);
}

RB *searchItemRB(RB *root, int x)
{
    while (root != NIL) {

        if (root->key == x)
            return root;

        if (x < root->key)
            root = root->left;
        else
            root = root->right;
    }

    return NIL;
}

RB *minimumRB(RB *p)
{
    while (p->left != NIL)
        p = p->left;

    return p;
}

void rbTransplant(RB **root, RB *u, RB *v)
{
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void rbDeleteFix(RB **root, RB *x)
{
    RB *w;

    while (x != *root && x->color == BLACK) {

        if (x == x->parent->left) {

            w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbLeftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK &&
                w->right->color == BLACK) {

                w->color = RED;
                x = x->parent;
            }

            else {

                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rbRightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;

                rbLeftRotate(root, x->parent);
                x = *root;
            }
        }

        else {

            w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rbRightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK &&
                w->left->color == BLACK) {

                w->color = RED;
                x = x->parent;
            }

            else {

                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rbLeftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;

                rbRightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    x->color = BLACK;
}

void deleteItemRB(RB **root, int x)
{
    RB *z = searchItemRB(*root, x);

    if (z == NIL)
        return;

    RB *y = z;
    RB *w;
    int old = y->color;

    if (z->left == NIL) {

        w = z->right;
        rbTransplant(root, z, z->right);
    }

    else if (z->right == NIL) {

        w = z->left;
        rbTransplant(root, z, z->left);
    }

    else {

        y = minimumRB(z->right);
        old = y->color;
        w = y->right;

        if (y->parent == z)
            w->parent = y;

        else {
            rbTransplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(root, z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    if (old == BLACK)
        rbDeleteFix(root, w);
}

void printRB(RB *p)
{
    if (p != NIL) {

        printRB(p->left);

        printf("%d(%s) ",
               p->key,
               p->color == RED ? "R" : "B");

        printRB(p->right);
    }
}

void deleteTreeRB(RB *p)
{
    if (p != NIL) {
        deleteTreeRB(p->left);
        deleteTreeRB(p->right);
        free(p);
    }
}


/* =========================================================
                         3. B-TREE
   ========================================================= */

#define BT 3

typedef struct BNode {
    int n, leaf;
    int key[2 * BT - 1];
    struct BNode *c[2 * BT];
} BNode;

BNode *createTreeB(int leaf)
{
    BNode *p = malloc(sizeof(BNode));

    p->n = 0;
    p->leaf = leaf;

    for (int i = 0; i < 2 * BT; i++)
        p->c[i] = NULL;

    return p;
}

BNode *searchItemB(BNode *p, int x)
{
    int i = 0;

    while (i < p->n && x > p->key[i])
        i++;

    if (i < p->n && x == p->key[i])
        return p;

    if (p->leaf)
        return NULL;

    return searchItemB(p->c[i], x);
}

void splitChild(BNode *p, int i)
{
    BNode *y = p->c[i];
    BNode *z = createTreeB(y->leaf);

    z->n = BT - 1;

    for (int j = 0; j < BT - 1; j++)
        z->key[j] = y->key[j + BT];

    if (!y->leaf)
        for (int j = 0; j < BT; j++)
            z->c[j] = y->c[j + BT];

    y->n = BT - 1;

    for (int j = p->n; j >= i + 1; j--)
        p->c[j + 1] = p->c[j];

    p->c[i + 1] = z;

    for (int j = p->n - 1; j >= i; j--)
        p->key[j + 1] = p->key[j];

    p->key[i] = y->key[BT - 1];
    p->n++;
}

void insertNonFull(BNode *p, int x)
{
    int i = p->n - 1;

    if (p->leaf) {

        while (i >= 0 && x < p->key[i]) {
            p->key[i + 1] = p->key[i];
            i--;
        }

        p->key[i + 1] = x;
        p->n++;
    }

    else {

        while (i >= 0 && x < p->key[i])
            i--;

        i++;

        if (p->c[i]->n == 2 * BT - 1) {

            splitChild(p, i);

            if (x > p->key[i])
                i++;
        }

        insertNonFull(p->c[i], x);
    }
}

void insertItemB(BNode **root, int x)
{
    if (!*root) {

        *root = createTreeB(1);
        (*root)->key[0] = x;
        (*root)->n = 1;

        return;
    }

    if (searchItemB(*root, x))
        return;

    BNode *r = *root;

    if (r->n == 2 * BT - 1) {

        BNode *s = createTreeB(0);

        *root = s;
        s->c[0] = r;

        splitChild(s, 0);

        if (x > s->key[0])
            insertNonFull(s->c[1], x);
        else
            insertNonFull(s->c[0], x);
    }

    else
        insertNonFull(r, x);
}

int findKey(BNode *p, int x)
{
    int i = 0;

    while (i < p->n && p->key[i] < x)
        i++;

    return i;
}

void removeFromLeaf(BNode *p, int i)
{
    for (int j = i + 1; j < p->n; j++)
        p->key[j - 1] = p->key[j];

    p->n--;
}

int getPred(BNode *p, int i)
{
    BNode *cur = p->c[i];

    while (!cur->leaf)
        cur = cur->c[cur->n];

    return cur->key[cur->n - 1];
}

int getSucc(BNode *p, int i)
{
    BNode *cur = p->c[i + 1];

    while (!cur->leaf)
        cur = cur->c[0];

    return cur->key[0];
}

void borrowPrev(BNode *p, int i)
{
    BNode *c = p->c[i];
    BNode *s = p->c[i - 1];

    for (int j = c->n - 1; j >= 0; j--)
        c->key[j + 1] = c->key[j];

    if (!c->leaf)
        for (int j = c->n; j >= 0; j--)
            c->c[j + 1] = c->c[j];

    c->key[0] = p->key[i - 1];

    if (!c->leaf)
        c->c[0] = s->c[s->n];

    p->key[i - 1] = s->key[s->n - 1];

    c->n++;
    s->n--;
}

void borrowNext(BNode *p, int i)
{
    BNode *c = p->c[i];
    BNode *s = p->c[i + 1];

    c->key[c->n] = p->key[i];

    if (!c->leaf)
        c->c[c->n + 1] = s->c[0];

    p->key[i] = s->key[0];

    for (int j = 1; j < s->n; j++)
        s->key[j - 1] = s->key[j];

    if (!s->leaf)
        for (int j = 1; j <= s->n; j++)
            s->c[j - 1] = s->c[j];

    c->n++;
    s->n--;
}

void mergeB(BNode *p, int i)
{
    BNode *c = p->c[i];
    BNode *s = p->c[i + 1];

    c->key[BT - 1] = p->key[i];

    for (int j = 0; j < s->n; j++)
        c->key[j + BT] = s->key[j];

    if (!c->leaf)
        for (int j = 0; j <= s->n; j++)
            c->c[j + BT] = s->c[j];

    for (int j = i + 1; j < p->n; j++)
        p->key[j - 1] = p->key[j];

    for (int j = i + 2; j <= p->n; j++)
        p->c[j - 1] = p->c[j];

    c->n += s->n + 1;
    p->n--;

    free(s);
}

void fillB(BNode *p, int i)
{
    if (i != 0 && p->c[i - 1]->n >= BT)
        borrowPrev(p, i);

    else if (i != p->n && p->c[i + 1]->n >= BT)
        borrowNext(p, i);

    else {
        if (i != p->n)
            mergeB(p, i);
        else
            mergeB(p, i - 1);
    }
}

void deleteBNode(BNode *p, int x);

void removeFromNonLeaf(BNode *p, int i)
{
    int x = p->key[i];

    if (p->c[i]->n >= BT) {

        int pred = getPred(p, i);
        p->key[i] = pred;

        deleteBNode(p->c[i], pred);
    }

    else if (p->c[i + 1]->n >= BT) {

        int succ = getSucc(p, i);
        p->key[i] = succ;

        deleteBNode(p->c[i + 1], succ);
    }

    else {

        mergeB(p, i);
        deleteBNode(p->c[i], x);
    }
}

void deleteBNode(BNode *p, int x)
{
    int i = findKey(p, x);

    if (i < p->n && p->key[i] == x) {

        if (p->leaf)
            removeFromLeaf(p, i);
        else
            removeFromNonLeaf(p, i);
    }

    else {

        if (p->leaf)
            return;

        if (p->c[i]->n < BT)
            fillB(p, i);

        if (i > p->n)
            deleteBNode(p->c[i - 1], x);
        else
            deleteBNode(p->c[i], x);
    }
}

void deleteItemB(BNode **root, int x)
{
    if (!*root)
        return;

    deleteBNode(*root, x);

    if ((*root)->n == 0) {

        BNode *t = *root;

        if ((*root)->leaf)
            *root = NULL;
        else
            *root = (*root)->c[0];

        free(t);
    }
}

void printB(BNode *p)
{
    if (!p)
        return;

    int i;

    for (i = 0; i < p->n; i++) {

        if (!p->leaf)
            printB(p->c[i]);

        printf("%d ", p->key[i]);
    }

    if (!p->leaf)
        printB(p->c[i]);
}

void deleteTreeB(BNode *p)
{
    if (!p)
        return;

    if (!p->leaf)
        for (int i = 0; i <= p->n; i++)
            deleteTreeB(p->c[i]);

    free(p);
}


/* =========================================================
                       4. B+ TREE
                       ORDER = 4
   ========================================================= */

#define ORDER 4

typedef struct BP {
    int key[ORDER];
    int n, leaf;

    struct BP *c[ORDER + 1];
    struct BP *next;
} BP;

BP *createTreeBP(int leaf)
{
    BP *p = malloc(sizeof(BP));

    p->n = 0;
    p->leaf = leaf;
    p->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        p->c[i] = NULL;

    return p;
}

BP *searchItemBP(BP *p, int x)
{
    if (!p)
        return NULL;

    if (p->leaf) {

        for (int i = 0; i < p->n; i++)
            if (p->key[i] == x)
                return p;

        return NULL;
    }

    int i = 0;

    while (i < p->n && x >= p->key[i])
        i++;

    return searchItemBP(p->c[i], x);
}

void leafInsert(BP *p, int x)
{
    int i = p->n - 1;

    while (i >= 0 && p->key[i] > x) {
        p->key[i + 1] = p->key[i];
        i--;
    }

    p->key[i + 1] = x;
    p->n++;
}

void splitBP(BP *p, int i)
{
    BP *a = p->c[i];
    BP *b = createTreeBP(a->leaf);

    if (a->leaf) {

        int mid = ORDER / 2;

        b->n = a->n - mid;

        for (int j = 0; j < b->n; j++)
            b->key[j] = a->key[mid + j];

        a->n = mid;

        b->next = a->next;
        a->next = b;

        for (int j = p->n; j > i; j--)
            p->c[j + 1] = p->c[j];

        for (int j = p->n - 1; j >= i; j--)
            p->key[j + 1] = p->key[j];

        p->key[i] = b->key[0];
        p->c[i + 1] = b;
        p->n++;
    }

    else {

        int mid = ORDER / 2;

        b->n = a->n - mid - 1;

        for (int j = 0; j < b->n; j++)
            b->key[j] = a->key[mid + 1 + j];

        for (int j = 0; j <= b->n; j++)
            b->c[j] = a->c[mid + 1 + j];

        int up = a->key[mid];

        a->n = mid;

        for (int j = p->n; j > i; j--)
            p->c[j + 1] = p->c[j];

        for (int j = p->n - 1; j >= i; j--)
            p->key[j + 1] = p->key[j];

        p->key[i] = up;
        p->c[i + 1] = b;
        p->n++;
    }
}

void insertNonFullBP(BP *p, int x)
{
    if (p->leaf) {
        leafInsert(p, x);
        return;
    }

    int i = 0;

    while (i < p->n && x >= p->key[i])
        i++;

    if (p->c[i]->n == ORDER - 1) {

        splitBP(p, i);

        if (x >= p->key[i])
            i++;
    }

    insertNonFullBP(p->c[i], x);
}

void insertItemBP(BP **root, int x)
{
    if (!*root) {

        *root = createTreeBP(1);

        (*root)->key[0] = x;
        (*root)->n = 1;

        return;
    }

    if (searchItemBP(*root, x))
        return;

    BP *r = *root;

    if (r->n == ORDER - 1) {

        BP *s = createTreeBP(0);

        *root = s;
        s->c[0] = r;

        splitBP(s, 0);

        if (x >= s->key[0])
            insertNonFullBP(s->c[1], x);
        else
            insertNonFullBP(s->c[0], x);
    }

    else
        insertNonFullBP(r, x);
}

int findChildBP(BP *p, int x)
{
    int i = 0;

    while (i < p->n && x >= p->key[i])
        i++;

    return i;
}

void updateKeysBP(BP *p)
{
    if (!p || p->leaf)
        return;

    for (int i = 1; i <= p->n; i++) {

        BP *q = p->c[i];

        while (!q->leaf)
            q = q->c[0];

        p->key[i - 1] = q->key[0];
    }

    for (int i = 0; i <= p->n; i++)
        updateKeysBP(p->c[i]);
}

void borrowLeftBP(BP *p, int i)
{
    BP *cur = p->c[i];
    BP *left = p->c[i - 1];

    if (cur->leaf) {

        for (int j = cur->n; j > 0; j--)
            cur->key[j] = cur->key[j - 1];

        cur->key[0] = left->key[left->n - 1];

        cur->n++;
        left->n--;
    }

    else {

        for (int j = cur->n; j > 0; j--)
            cur->key[j] = cur->key[j - 1];

        for (int j = cur->n + 1; j > 0; j--)
            cur->c[j] = cur->c[j - 1];

        cur->key[0] = p->key[i - 1];
        cur->c[0] = left->c[left->n];

        cur->n++;
        left->n--;
    }
}

void borrowRightBP(BP *p, int i)
{
    BP *cur = p->c[i];
    BP *right = p->c[i + 1];

    if (cur->leaf) {

        cur->key[cur->n] = right->key[0];
        cur->n++;

        for (int j = 1; j < right->n; j++)
            right->key[j - 1] = right->key[j];

        right->n--;
    }

    else {

        cur->key[cur->n] = p->key[i];
        cur->c[cur->n + 1] = right->c[0];

        cur->n++;

        p->key[i] = right->key[0];

        for (int j = 1; j < right->n; j++)
            right->key[j - 1] = right->key[j];

        for (int j = 1; j <= right->n; j++)
            right->c[j - 1] = right->c[j];

        right->n--;
    }
}

void mergeBP(BP *p, int i)
{
    BP *a = p->c[i];
    BP *b = p->c[i + 1];

    if (a->leaf) {

        for (int j = 0; j < b->n; j++)
            a->key[a->n + j] = b->key[j];

        a->n += b->n;
        a->next = b->next;
    }

    else {

        a->key[a->n] = p->key[i];

        for (int j = 0; j < b->n; j++)
            a->key[a->n + 1 + j] = b->key[j];

        for (int j = 0; j <= b->n; j++)
            a->c[a->n + 1 + j] = b->c[j];

        a->n += b->n + 1;
    }

    for (int j = i; j < p->n - 1; j++)
        p->key[j] = p->key[j + 1];

    for (int j = i + 1; j < p->n; j++)
        p->c[j] = p->c[j + 1];

    p->n--;

    free(b);
}

void deleteLeafBP(BP *p, int x)
{
    int i = 0;

    while (i < p->n && p->key[i] != x)
        i++;

    if (i == p->n)
        return;

    for (int j = i; j < p->n - 1; j++)
        p->key[j] = p->key[j + 1];

    p->n--;
}

void deleteBPNode(BP *p, int x)
{
    if (p->leaf) {
        deleteLeafBP(p, x);
        return;
    }

    int i = findChildBP(p, x);

    deleteBPNode(p->c[i], x);

    /*
       A non-root leaf/internal node must have
       at least one key in this order-4 implementation.
    */

    if (p->c[i]->n == 0) {

        if (i > 0 && p->c[i - 1]->n > 1)
            borrowLeftBP(p, i);

        else if (i < p->n && p->c[i + 1]->n > 1)
            borrowRightBP(p, i);

        else if (i < p->n)
            mergeBP(p, i);

        else
            mergeBP(p, i - 1);
    }
}

void deleteItemBP(BP **root, int x)
{
    if (!*root)
        return;

    if (!searchItemBP(*root, x))
        return;

    deleteBPNode(*root, x);

    if (!(*root)->leaf && (*root)->n == 0) {

        BP *t = *root;

        *root = (*root)->c[0];

        free(t);
    }

    updateKeysBP(*root);
}

void displayBP(BP *root)
{
    if (!root)
        return;

    BP *p = root;

    while (!p->leaf)
        p = p->c[0];

    while (p) {

        for (int i = 0; i < p->n; i++)
            printf("%d ", p->key[i]);

        p = p->next;
    }
}

void deleteTreeBP(BP *p)
{
    if (!p)
        return;

    if (!p->leaf)
        for (int i = 0; i <= p->n; i++)
            deleteTreeBP(p->c[i]);

    free(p);
}


/* =========================================================
                         MAIN FUNCTION
   ========================================================= */

int main()
{
    /* ---------------- AVL ---------------- */

    AVL *avl = NULL;

    avl = insertItemAVL(avl, 30);
    avl = insertItemAVL(avl, 20);
    avl = insertItemAVL(avl, 40);
    avl = insertItemAVL(avl, 10);
    avl = insertItemAVL(avl, 25);

    printf("AVL Tree: ");
    printAVL(avl);

    printf("\nSearch 25: ");
    printf(searchItemAVL(avl,25) ? "Found" : "Not Found");

    avl = deleteItemAVL(avl,20);

    printf("\nAfter deleting 20: ");
    printAVL(avl);


    /* ---------------- RED-BLACK ---------------- */

    initRB();

    RB *rb = NIL;

    insertItemRB(&rb,30);
    insertItemRB(&rb,20);
    insertItemRB(&rb,40);
    insertItemRB(&rb,10);
    insertItemRB(&rb,25);

    printf("\n\nRed-Black Tree: ");
    printRB(rb);

    printf("\nSearch 25: ");
    printf(searchItemRB(rb,25) != NIL ? "Found" : "Not Found");

    deleteItemRB(&rb,20);

    printf("\nAfter deleting 20: ");
    printRB(rb);


    /* ---------------- B-TREE ---------------- */

    BNode *bt = NULL;

    insertItemB(&bt,10);
    insertItemB(&bt,20);
    insertItemB(&bt,5);
    insertItemB(&bt,6);
    insertItemB(&bt,12);
    insertItemB(&bt,30);
    insertItemB(&bt,7);
    insertItemB(&bt,17);

    printf("\n\nB-Tree: ");
    printB(bt);

    printf("\nSearch 12: ");
    printf(searchItemB(bt,12) ? "Found" : "Not Found");

    deleteItemB(&bt,6);

    printf("\nAfter deleting 6: ");
    printB(bt);


    /* ---------------- B+ TREE ---------------- */

    BP *bp = NULL;

    insertItemBP(&bp,10);
    insertItemBP(&bp,20);
    insertItemBP(&bp,5);
    insertItemBP(&bp,30);
    insertItemBP(&bp,15);
    insertItemBP(&bp,25);
    insertItemBP(&bp,35);

    printf("\n\nB+ Tree: ");
    displayBP(bp);

    printf("\nSearch 25: ");
    printf(searchItemBP(bp,25) ? "Found" : "Not Found");

    deleteItemBP(&bp,20);

    printf("\nAfter deleting 20: ");
    displayBP(bp);


    /* ---------------- FREE MEMORY ---------------- */

    deleteTreeAVL(avl);
    deleteTreeRB(rb);
    deleteTreeB(bt);
    deleteTreeBP(bp);

    free(NIL);

    return 0;
}
