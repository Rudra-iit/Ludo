#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <SDL.h>

using namespace std;

int main () {
    int gd = DETECT, gm;
    initgraph (&gd, &gm, (char*)"");
    circle (0, 0, 5);
    return 0;
}