#include <stdio.h>
#include <time.h>

void print () {
    for (int i=0; i<100; i++) {
        printf ("Time.\n");
    }
}

int main () {
    clock_t t;
    double time;
    t = clock ();
    print ();
    t = clock () - t;
    time = ((double)t)/CLOCKS_PER_SEC;
    printf ("%f\n", time);
    return 0;
}