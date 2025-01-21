#include <stdio.h>
#include <stdlib.h>

int board_1[10][10], board_2[10][10], snake[10][10], i, j;

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

    int y1=1;
    int y2=1;

    while (1) {

        printf ("\nRed: ");
        scanf (" %c", &dice);

        if (dice!='y') {
            printf ("Sorry, press 'y' to try again.\n");
        }

        else {

            int x = rand () % 5 + 1;
            y1 = y1+x;
            printf ("The dice roles %d\n", x);

            int a = rand () % 40 + 1;
            int b = rand () % 20 + 1;
            int c = rand () % 45 + 1;
            int d = rand () % 30 + 1;

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

                    board_1[i][j] = snake[i][j];

                    if (y1==a) {
                        if (snake[i][j]==b) {
                            board_1[i][j] = 0;
                            y1 = b;
                        }
                    }

                    else if (y1==c) {
                        if (snake[i][j]==d) {
                            board_1[i][j] = 0;
                            y1 = d;
                        }
                    }

                    else if (y1==snake[i][j]) {
                        board_1[i][j] = 0;
                    }

                }
            }

            print (board_1);

            if (y1>100) {
                y1=y1-x;
            }

        }

        if (y1==100) {
            printf ("Red won!");
            break;
        }

        printf ("\nBlue: ");
        scanf (" %c", &dice);
        if (dice!='y') {
            printf ("Sorry, press 'y' to try again.\n");
        }

        else {

            int l = rand () % 5 + 1;
            y2 = y2+l;
            printf ("The dice roles %d\n", l);

            int a = rand () % 50 + 1;
            int b = rand () % 30 + 1;
            int c = rand () % 40 + 1;
            int d = rand () % 20 + 1;

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

                    board_2[i][j] = snake[i][j];

                    if (y2==a) {
                        if (snake[i][j]==b) {
                            board_2[i][j] = 0;
                            y2 = b;
                        }
                    }

                    else if (y2==c) {
                        if (snake[i][j]==d) {
                            board_2[i][j] = 0;
                            y2 = d;
                        }
                    }

                    else if (y2==snake[i][j]) {
                        board_2[i][j] = 0;
                    }

                }
            }

            print (board_2);

            if (y2>100) {
                y2=y2-l;
            }

        }

        if (y2==100) {
            printf ("Blue won!");
            break;
        }

    }
    return 0;
}