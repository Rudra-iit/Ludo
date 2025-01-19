#include <stdio.h>
#include <stdlib.h>

char matrix[20][20];
int i=0, j=0;

typedef struct Node {
    int x, y;
    struct Node *left, *right, *up, *down;
} Node;

Node* make_node (int x, int y) {
    Node* newNode = (Node*) malloc (sizeof (Node));
    newNode->x = x;
    newNode->y = y;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->up = NULL;
    newNode->down = NULL;
    return newNode;
}

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

Node* tree (char matrix[20][20], int x, int y, int row, int column) {
    if (x<0 || x>=row || y<0 || y>=column || matrix[x][y]=='#') {
        return NULL;
    }
    Node* node = make_node (x, y);
    matrix[x][y] = '#';
    node->left = tree (matrix, x, y-1, row, column);
    node->right = tree (matrix, x, y+1, row, column);
    node->up = tree (matrix, x-1, y, row, column);
    node->down = tree (matrix, x+1, y, row, column);
    return node;
}

void print_matrix () {
    for (i=0; i<20; i++) {
        for (j=0; j<20; j++) {
            printf ("%c", matrix[i][j]);
        }
        printf ("\n");
    }
    printf ("\n");
}

void print_tree (Node* root) {
    if (root==NULL) {
        return;
    }
    printf ("%d %d\n", root->x, root->y);
    print_tree (root->left);
    print_tree (root->right);
    print_tree (root->up);
    print_tree (root->down);
}

int main () {
    maze_1 ();
    print_matrix ();
    Node* root = tree (matrix, 0, 5, 20, 20);
    print_tree (root);
    /*
    matrix [0][5] = '$';
    print_matrix ();
    int x = rand () % 6 + 1;
    printf ("%d\n", x);
    matrix [x-3][5+3] = '$';
    print_matrix ();
    */
    return 0;
}