#include <stdio.h>
#include <graphics.h>

struct a {
    int red, blue, green, yellow;
} a;
int snake[2];
int ladder[2];
int board[21][21];
int dice;

void normal () {
    a.red = board[20][9];
    if (dice!=6) {
        if (dice==1) {
            a.red = board[20][dice];
        }
    }
    a.blue = board[9][0];
    a.yellow = board[0][9];
    a.green = board[9][20];
}
void snake ();
void labyrinth ();

int main () {
    return 0;
}