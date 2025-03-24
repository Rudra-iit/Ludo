#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

#pragma comment(lib, "ws2_32.lib")

int board[10][10], snake[10][10], i, j, w=0, q=0, p=0, d=0;

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

int main() {
    for (i=10-1; i>=0; i--) {
        for (j=10-1; j>=0; j--) {
            snake[i][j] = i*10 + (j+1);
        }
    }

    int y = 1;
    int life = 10;

    int k=0;
    int time_limit = 10; // Time limit in seconds

    char name[10];
    scanf (" %s", name);

    while (1) {

        int m, n, o;
        int m1, n1, o1;

        clock_t start_time = clock();

        printf("-\nRole %d: Please role dice within %d seconds...\n", k + 1, time_limit);

        int input_received = 0; // Flag to check if input is received

        while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit) {

            if (_kbhit()) { // Check if a key has been pressed

                char c = getch(); // Capture the key press
                printf("%s entered: '%c'\n", name, c);

                if (c=='y') {
                    int x = rand() % 5 + 1;
                    y = y+x;

                    printf ("Dice roled: %d\n", x);

                    // Random numbers as snake or ladder
                    int a = rand() % 90 + 1;
                    int b = rand() % 50 + 1;

                    if (a>b) {
                        printf ("Snake exists between %d and %d.\n", a, b);
                    }

                    else {
                        printf ("Ladder exists between %d and %d.\n", a, b);
                    }

                    for (i=0; i<10; i++) {
                        for (j=0; j<10; j++) {
                            board[i][j] = snake[i][j];
                            
                            // When snake/ladder comes on the way
                            if (y==a) {
                                if (snake[i][j] == b) {
                                    board[i][j] = 0;
                                    y = b;
                                }
                            }

                            // When they don't
                            else if (y==snake[i][j]) {
                                board[i][j] = 0;
                            }
                        }
                    }

                    print (board);
                    
                    // Check when the game's ending
                    if (y==100) {
                        w=1;
                    }
                    
                    // If the dice count goes out of 100 without the game finishing
                    if (y>100) {
                        y = y-x;
                    }
                    
                }
                else {
                    printf ("Try again.\n");
                }
                input_received = 1;
                break; // Exit the loop if a key is pressed

            }

        }

        if (!input_received) {

            // Not timely input: life lost
            printf("No input received on this iteration.\n");
            life--;
            printf ("Life is %d\n", life);

        }

        if (life==0) {

            // Disqualified
            printf ("Game over.\n");
            break;

        }

        if (w==1) {

            // Finish the game
            printf ("%s won.\n", name);
            break;

        }
        k++;

    }

    return 0;
}