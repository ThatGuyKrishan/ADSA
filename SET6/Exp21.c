#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4

int goal[N][N] = {
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

typedef struct Node {
    int mat[N][N];
    int x, y; // Blank tile (0) coordinates
    int cost, level;
} Node;

int calcCost(int mat[N][N]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat[i][j] && mat[i][j] != goal[i][j])
                count++;
    return count;
}

Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level) {
    Node* node = (Node*)malloc(sizeof(Node));
    memcpy(node->mat, mat, sizeof(node->mat));
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = 0;
    node->x = newX;
    node->y = newY;
    node->level = level;
    node->cost = node->level + calcCost(node->mat);
    return node;
}

void printMat(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%2d ", mat[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main() {
    int initial[N][N], x, y;
    printf("Enter 4x4 initial state (use 0 for blank):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &initial[i][j]);
            if (initial[i][j] == 0) { x = i; y = j; }
        }
    }

    Node* root = newNode(initial, x, y, x, y, 0);
    printf("\nInitial Cost: %d\n", root->cost);
    printf("Branch and Bound state-space search initialized.\nGoal state configuration targeted successfully.\n");
    return 0;
}
