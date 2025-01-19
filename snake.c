#include <stdio.h>
#include <stdlib.h>

int board[10][10], i, j;

void print (int board[10][10]) {
    printf ("\n");
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
    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            board[i][j] = i*10 + (j+1);
        }
    }
    print (board);
    int y=0;
    while (y<=50) {
    int x = rand () % 5 + 1;
    y = x+y;
    int s = rand () % 90 + 1;
    int e = rand () % 80 + 1;
    printf ("\nThe dice roles %d, snake's head is %d and tail is %d\n", x, s, e);
    for (i=0; i<10; i++) {
        for (j=0; j<10; j++) {
            if (y==s) {
                if (board[i][j]==e) {
                    board[i][j] = 0;
                }
            }
            else if (board[i][j]==y) {
                board[i][j] = 0;
            }
        }
    }
    print (board);
    }
    return 0;
}