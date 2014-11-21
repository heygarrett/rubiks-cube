#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turns.h"
#include "valid.h"

void make_move(unsigned char *cube, char face, int turns) {

    int redCubies[8] = {0, 5, 7, 2, 1, 3, 6, 4};
    int redSwap[2] = {0, 2};
    int greenCubies[8] = {0, 12, 17, 5, 3, 8, 15, 10};
    int greenSwap[2] = {1, 2};
    int yellowCubies[8] = {5, 17, 19, 7, 6, 10, 18, 11};
    int yellowSwap[2] = {0, 1};
    int blueCubies[8] = {7, 19, 14, 2, 4, 11, 16, 9};
    int blueSwap[2] = {1, 2};
    int orangeCubies[8] = {17, 12, 14, 19, 18, 15, 13, 16};
    int orangeSwap[2] = {0, 2};
    int whiteCubies[8] = {0, 2, 14, 12, 1, 9, 13, 8};
    int whiteSwap[2] = {0, 1};

    int *color = NULL;
    int *swap = NULL;
    if (face == 'R') {
        color = redCubies;
        swap = redSwap;
    } else if (face == 'G') {
        color = greenCubies;
        swap = greenSwap;
    } else if (face == 'Y') {
        color = yellowCubies;
        swap = yellowSwap;
    } else if (face == 'B') {
        color = blueCubies;
        swap = blueSwap;
    } else if (face == 'O') {
        color = orangeCubies;
        swap = orangeSwap;
    } else if (face == 'W') {
        color = whiteCubies;
        swap = whiteSwap;
    }

    char temp;
    while (turns > 0) {
        temp = switchColors(cube[color[0]], swap);
        cube[color[0]] = switchColors(cube[color[1]], swap);
        cube[color[1]] = switchColors(cube[color[2]], swap);
        cube[color[2]] = switchColors(cube[color[3]], swap);
        cube[color[3]] = temp;
        temp = switchColors(cube[color[4]], swap);
        cube[color[4]] = switchColors(cube[color[5]], swap);
        cube[color[5]] = switchColors(cube[color[6]], swap);
        cube[color[6]] = switchColors(cube[color[7]], swap);
        cube[color[7]] = temp;
        --turns;
    }
}

unsigned char switchColors(unsigned char cubie, int *swap) {
    unsigned char colors[3];
    get_cubie_colors(cubie, colors);
    unsigned char temp = colors[swap[0]];
    colors[swap[0]] = colors[swap[1]];
    colors[swap[1]] = temp;
    return set_cubie_colors(colors[0], colors[1], colors[2]);
}
