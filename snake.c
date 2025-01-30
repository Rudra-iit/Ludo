#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int board[10][10], snake[10][10], i, j;

void print (int board[10][10]) {

    printf ("-\n");

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

    char dice;

    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            snake[i][j] = i*10 + (j+1);
        }
    }

    int y=1;

    while (1) {

        printf ("\nRole: ");
        scanf (" %c", &dice);

        if (dice!='y') {
            printf ("Sorry, press 'y' to try again.\n");
        }

        else {

            int x = rand () % 5 + 1;
            y = y+x;
            printf ("The dice roles %d\n", x);

            int a = rand () % 90 + 1;
            int b = rand () % 80 + 1;
            int c = rand () % 70 + 1;
            int d = rand () % 40 + 1;

            if (a>b) {
                printf ("Snake exists between %d & %d\n", a, b);
            }
            else {
                printf ("Ladder exists between %d & %d\n", a, b);
            }

            if (c>d) {
                printf ("Snake exists between %d & %d\n", c, d);
            }
            else {
                printf ("Ladder exists between %d & %d\n", c, d);
            }

            for (i=0; i<10; i++) {
                for (j=0; j<10; j++) {

                    board[i][j] = snake[i][j];

                    if (y==a) {
                        if (snake[i][j]==b) {
                            board[i][j] = 0;
                            y = b;
                        }
                    }

                    else if (y==c) {
                        if (snake[i][j]==d) {
                            board[i][j] = 0;
                            y = d;
                        }
                    }

                    else if (y==snake[i][j]) {
                        board[i][j] = 0;
                    }

                }
            }

            print (board);

            if (y==100) {
                printf ("Game completed!");
                break;
            }

            if (y>100) {
                y=y-x;
            }
        
        }

    }
    return 0;
}