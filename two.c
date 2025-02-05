#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>


int board[10][10], snake[10][10], i, j, w=0, q=0;


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

    int y=1, z=1, life1 = 10, life2 = 10;
    int iterations = 0;
    int time_limit_user1 = 2; // Time limit for the first user in seconds
    int time_limit_user2 = 2; // Time limit for the second user in seconds

    // The main loop of the game

    while (1) {

        clock_t start_time;
        int input_received_user1 = 0; // Flag to check if input is received from player 1
        int input_received_user2 = 0; // Flag to check if input is received from player 2

        // First player's input
        printf("Player 1, please enter a character within %d seconds...\n", time_limit_user1);

        start_time = clock();

        while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit_user1) {

            if (_kbhit()) { // Check if a key has been pressed

                char c = getch(); // Capture the key press
                printf("User 1 entered: '%c'\n", c);

                if (c=='y') {

                    int x = rand() % 5 + 1;
                    y = y+x;

                    printf ("Dice roled: %d\n", x);

                    // Random numbers as snake head and tail
                    // Or ladder bottom and top
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

                            // When the player reaches a snake's head or ladder's bottom
                            if (y==a) {
                                if (snake[i][j] == b) {
                                    board[i][j] = 0;
                                    y = b;
                                }
                            }
                            else if (y==snake[i][j]) {
                                board[i][j] = 0;
                            }
                        }
                    }

                    print (board);
                    
                    // When game ends
                    if (y==100) {
                        w=1;
                    }
                    

                    // When the count surpasses 100
                    if (y>100) {
                        y = y-x;
                    }
                    
                }

                // If you pressed wrong key:
                else {
                    printf ("Try again.\n");
                }

                input_received_user1 = 1;
                break; // Exit the loop if a key is pressed
            }
        }

        if (!input_received_user1) {
            
            // Count life at failure to role dice in time
            printf("No input from User 1.\n");
            life1--;
            printf ("Life is %d.\n", life1);

        }
        
        //Too few lives
        if (life1==0) {
            printf ("Game over.\n");
            break;
        }
        
        // When the game comes to an end
        if (w==1) {
            printf ("Game completed.");
            break;
        }



        // Second player's input

        printf("Player 2, please enter a character within %d seconds...\n", time_limit_user2);
        start_time = clock();

        while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit_user2) {

            if (_kbhit()) { // Check if a key has been pressed

                char c = getch(); // Capture the key press
                printf("User 2 entered: '%c'\n", c);

                if (c=='y') {
                    int x = rand() % 5 + 1;
                    z = z+x;

                    printf ("Dice roled %d\n", x);

                    int w1 = rand () % 80 + 1;
                    int w2 = rand () % 40 + 1;

                    if (w1>w2) {
                        printf ("Snake exists between %d and %d", w1, w2);
                    }

                    else {
                        printf ("Ladder exists between %d and %d", w1, w2);
                    }

                    for (i=0; i<10; i++) {
                        for (j=0; j<10; j++) {
                            board[i][j] = snake[i][j];

                            if (z==w1) {
                                if (snake[i][j] == w2) {
                                    board[i][j] = 0;
                                    z = w2;
                                }
                            }

                            else if (z==snake[i][j]) {
                                board[i][j] = 0;

                            }
                        }
                    }
                    
                    print (board);

                    if (z==100) {
                        q = 1;
                    }

                    if (z>100) {
                        z = z-x;
                    }

                }

                else {
                    printf ("Try again.\n");
                }

                input_received_user2 = 1;
                break; // Exit the loop if a key is pressed
            }
        }

        if (!input_received_user2) {

            printf("No input from User 2.\n");
            life2--;
            printf ("Life is %d.\n", life2);
        }
        
        if (life2==0) {

            printf ("Game over.\n");
            break;
        }

        if (q==1) {

            printf ("Game completed.\n");
            break;
        }


        iterations++;;
    }

    return 0;
}