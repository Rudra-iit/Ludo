#include <stdio.h>
#include <stdlib.h>

char matrix[20][20];
int i=0, j=0;

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* treeNode (int d) {
    struct Node* newNode = (struct Node*) malloc (sizeof (struct Node*));
    newNode->data = d;
    newNode->left = NULL;
    newNode->right = NULL;
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

void tree (char matrix[20][20]) {
    int i, j;

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
    matrix [0][5] = '$';
    print ();
    int x = rand () % 6 + 1;
    printf ("%d\n", x);
    matrix [x-3][5+3] = '$';
    print ();
    return 0;
}

/*#include <stdio.h>
#include <stdlib.h>

struct node {
    int num;                
    struct node *nextptr;   
} *stnode;                  

void createNodeList (int n) {
    struct node *fnNode, *tmp;
    int num, i;
    stnode = (struct node *)malloc(sizeof(struct node));
    if (stnode == NULL) {
        printf ("Memory can not be allocated.");
    } 
    else {
        printf ("Node input:\n");
        scanf ("%d", &num);
        stnode->num = num;      
        stnode->nextptr = NULL; 
        tmp = stnode;
        for (i=2; i<=n; i++) {
            fnNode = (struct node *)malloc(sizeof(struct node));
            if (fnNode == NULL) {
                printf("Memory can not be allocated.");
                break;
            } 
            else {
                scanf("%d", &num);
                fnNode->num = num;      
                fnNode->nextptr = NULL;
                tmp->nextptr = fnNode; 
                tmp = tmp->nextptr;   
            }
        }
    }
}

void displayList () {
    struct node *tmp;
    if (stnode == NULL) {
        printf("List is empty.");
    } 
    else {
        tmp = stnode;
        while (tmp != NULL) {
            printf ("%d ", tmp->num); 
            tmp = tmp->nextptr;
        }
    }
}

int main () {
    int n;
    printf ("Number of nodes: ");
    scanf ("%d", &n);
    createNodeList (n);
    printf ("Data entered in the list: \n");
    displayList ();
    return 0;
}*/