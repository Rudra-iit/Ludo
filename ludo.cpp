#include <stdio.h>

char matrix[20][20];
int i=0, j=0;

void maze_1 () {
    FILE *f = fopen ("maze_1.txt", "r");
    char c;
    if (f==NULL) {
        printf ("Maze not found!\n");
        return;
    }
    while ((c = fgetc (f)) != EOF) {
        if (c=='\n') {
            i++;
            j=0;
        }
        else {
            matrix[i][j++] = c;
        }
    }
    fclose (f);
}

void print () {
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            printf ("%c", matrix[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

int main () {
    maze_1 ();
    print ();
    char dice;
    scanf ("%c", &dice);
    matrix [0][5] = dice;
    print ();
    return 0;
}