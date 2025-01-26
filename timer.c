#include <stdio.h>
#include <time.h>
#include <conio.h>  // For _kbhit() function on Windows

int main() {
    printf("Press any key within 5 seconds to avoid disqualification.\n");

    clock_t start_time = clock();  // Record start time
    clock_t time_limit = 5 * CLOCKS_PER_SEC;  // 5 seconds limit

    while ((clock() - start_time) < time_limit) {
        if (_kbhit()) {  // Check if a key has been pressed
            printf("You pressed a key in time! You are safe.\n");
            return 0;
        }
    }

    printf("Time is up! You are disqualified.\n");
    return 0;
}