#include <stdio.h>
#include <time.h>
#include <conio.h>  // For _kbhit() function on Windows

int main() {
    int num_iterations = 5;  // Number of iterations

    for (int i = 1; i <= num_iterations; i++) {
        printf("Iteration %d: Press any key within 5 seconds...\n", i);

        clock_t start_time = clock();  // Record start time
        clock_t time_limit = 5 * CLOCKS_PER_SEC;  // 5 seconds limit

        while ((clock() - start_time) < time_limit) {
            if (_kbhit()) {  // Check if a key has been pressed
                printf("You pressed a key in time!\n");
                break;  // Exit the while loop and proceed to the next iteration
            }
        }

        if ((clock() - start_time) >= time_limit) {
            printf("Time is up! Moving to the next iteration.\n");
        }
    }

    printf("All iterations are completed.\n");
    return 0;
}