#include <stdio.h>

char matrix[20][20];

void maze_1 () {
    FILE *f = fopen ("maze_1.txt", "r");
    int i, j;
    char dice;
    if (f==NULL) {
        printf ("Maze not found!\n");
    }
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            while ((matrix[i][j] = fgetc (f)) != EOF) {   
                printf ("%c", matrix[i][j]);
            }
        }
    }
    fclose (f);
}

int main () {
    maze_1 ();
    return 0;
}