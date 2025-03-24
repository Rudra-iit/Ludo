#include <winsock2.h>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_CLIENTS 1

int board[10][10], snake[10][10], i, j, w=0, k=0, life = 10;
char name[5];

int se[4] = {44, 93, 27, 55};
int ladder[4] = {67, 34, 23, 94};

void error(const char *msg) {
    perror(msg);
    exit(1);
}

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

    scanf ("%s", name);
    
    int time_limit = 5;

    int y = 0;
    
    clock_t start_time = clock();

    printf("-\nRole %d: Please role dice within %d seconds...\n", k + 1, time_limit);

    int input_received = 0; // Flag to check if input is received

    while (1) {

    while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit) {

        if (_kbhit()) { // Check if a key has been pressed

            char c = getch(); // Capture the key press
            printf("%s entered: '%c'\n", name, c);

            if (c=='y') {
                
                int x = rand() % 5 + 1;
                y = y+x;

                printf ("Dice roled: %d\n", x);

                // Random numbers as snake or ladder
                int a = rand() % 3 + 1;
                int c = rand() % 3 + 1;
                int b = 10;
                int d = 8;
                printf ("Snake exists between %d and %d.\n", se[a], b);
                
                printf ("Ladder exists between %d and %d.\n", ladder[c], d);
                

                for (i=0; i<10; i++) {
                    for (j=0; j<10; j++) {
                        board[i][j] = snake[i][j];
                        
                        // When snake/ladder comes on the way
                        if (y==se[a]) {
                            if (snake[i][j] == b) {
                                board[i][j] = 0;
                                y = b;
                            }
                        }

                        else if (y==d) {
                            if (snake[i][j] == ladder[c]) {
                                board[i][j] = 0;
                                y = ladder[c];
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

    if (y>100) {
        y = y-10;
    }

    if (life==0) {
        printf ("Game over.\n");
        break;
    }

    if (w==1) {
        printf ("%s won!\n", name);
        break;
    }

    k++;
    }
    return 0;
}