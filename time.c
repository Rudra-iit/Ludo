#include <conio.h>
#include <stdio.h>
#include <time.h>

int main() {
    int iterations = 10;
    int time_limit = 2; // Time limit in seconds

    for (int i = 0; i < iterations; i++) {
        clock_t start_time = clock();
        printf("Iteration %d: Please enter a character within %d seconds...\n", i + 1, time_limit);

        int input_received = 0; // Flag to check if input is received

        while ((clock() - start_time) / CLOCKS_PER_SEC < time_limit) {
            if (_kbhit()) { // Check if a key has been pressed
                char c = getch(); // Capture the key press
                printf("You entered: '%c'\n", c);
                input_received = 1;
                break; // Exit the loop if a key is pressed
            }
        }

        if (!input_received) {
            printf("No input received on this iteration.\n");
        }
    }

    return 0;
}