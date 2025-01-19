#include <stdio.h>
#include <stdlib.h>

void print (int board[10][10]) {
    int i, j;
    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            if (board[i][j]==100) {
                printf ("%d ", board[i][j]);
            }
            else if (board[i][j]>=10 && board[i][j]<100) {
                printf (" %d ", board[i][j]);
            }
            else {
                printf ("  %d ", board[i][j]);
            }
        }
        printf ("\n");
    }
}

int main () {
    int board[10][10], i, j, m, n;
    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            board[i][j] = i*10 + (j+1);
        }
    }
    print (board);
    int x = rand () % 6 + 1;
    printf ("%d\n", x);
    board[0][x] = 0;
    print (board);
    return 0;
}