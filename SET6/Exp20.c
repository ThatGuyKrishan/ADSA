#include <stdio.h>
#include <math.h>

int board[20], count = 0;

int place(int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return 0;
    return 1;
}

void nqueens(int row, int n) {
    for (int col = 0; col < n; col++) {
        if (place(row, col)) {
            board[row] = col;
            if (row == n - 1) {
                count++;
                printf("Solution %d:\n", count);
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++)
                        printf("%c ", board[i] == j ? 'Q' : '.');
                    printf("\n");
                }
                printf("\n");
            } else {
                nqueens(row + 1, n);
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the number of queens (N): ");
    scanf("%d", &n);
    nqueens(0, n);
    printf("Total solutions: %d\n", count);
    return 0;
}
