#include <stdio.h>
#include <stdlib.h>

char maze[20][20];
int i, j;

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
            maze[i][j++] = c;
        }
    }
    fclose (f);
}

void print_matrix () {
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            printf ("%c", maze[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

int main() {
    maze_1 ();
    print_matrix ();
    return 0;
}