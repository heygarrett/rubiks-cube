#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turns.h"
#include "valid.h"

void turnRed(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {0, 2};
        int temp = switchColors(cube[0], swap);
        cube[0] = switchColors(cube[5], swap);
        cube[5] = switchColors(cube[7], swap);
        cube[7] = switchColors(cube[2], swap);
        cube[2] = temp;
        temp = switchColors(cube[1], swap);
        cube[1] = switchColors(cube[3], swap);
        cube[3] = switchColors(cube[6], swap);
        cube[6] = switchColors(cube[4], swap);
        cube[4] = temp;
        --turns;
    }
}

void turnGreen(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {1, 2};
        int temp = switchColors(cube[0], swap);
        cube[0] = switchColors(cube[12], swap);
        cube[12] = switchColors(cube[17], swap);
        cube[17] = switchColors(cube[5], swap);
        cube[5] = temp;
        temp = switchColors(cube[3], swap);
        cube[3] = switchColors(cube[8], swap);
        cube[8] = switchColors(cube[15], swap);
        cube[15] = switchColors(cube[10], swap);
        cube[10] = temp;
        --turns;
    }
}

void turnYellow(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {0, 1};
        int temp = switchColors(cube[5], swap);
        cube[5] = switchColors(cube[17], swap);
        cube[17] = switchColors(cube[19], swap);
        cube[19] = switchColors(cube[7], swap);;
        cube[7] = temp;
        temp = switchColors(cube[6], swap);
        cube[6] = switchColors(cube[10], swap);
        cube[10] = switchColors(cube[18], swap);
        cube[18] = switchColors(cube[11], swap);;
        cube[11] = temp;
        --turns;
    }
}

void turnBlue(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {1, 2};
        int temp = switchColors(cube[7], swap);
        cube[7] = switchColors(cube[19], swap);
        cube[19] = switchColors(cube[14], swap);
        cube[14] = switchColors(cube[2], swap);
        cube[2] = temp;
        temp = switchColors(cube[4], swap);
        cube[4] = switchColors(cube[11], swap);
        cube[11] = switchColors(cube[16], swap);
        cube[16] = switchColors(cube[9], swap);;
        cube[9] = temp;
        --turns;
    }
}

void turnOrange(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {0, 2};
        int temp = switchColors(cube[17], swap);
        cube[17] = switchColors(cube[12], swap);
        cube[12] = switchColors(cube[14], swap);
        cube[14] = switchColors(cube[19], swap);
        cube[19] = temp;
        temp = switchColors(cube[18], swap);
        cube[18] = switchColors(cube[15], swap);
        cube[15] = switchColors(cube[13], swap);
        cube[13] = switchColors(cube[16], swap);
        cube[16] = temp;
        --turns;
    }
}

void turnWhite(unsigned char *cube, int turns) {
    while (turns > 0) {
        int swap[2] = {0, 1};
        int temp = switchColors(cube[0], swap);
        cube[0] = switchColors(cube[2], swap);
        cube[2] = switchColors(cube[14], swap);
        cube[14] = switchColors(cube[12], swap);
        cube[12] = temp;
        temp = switchColors(cube[1], swap);
        cube[1] = switchColors(cube[9], swap);
        cube[9] = switchColors(cube[13], swap);
        cube[13] = cube[8];
        cube[8] = temp;
        --turns;
    }
}

unsigned char switchColors(unsigned char cubie, int *swap) {
    unsigned char colors[3];
    getCubieColors(cubie, colors);
    unsigned char temp = colors[swap[0]];
    colors[swap[0]] = colors[swap[1]];
    colors[swap[1]] = temp;
    return setCubieColors(colors[0], colors[1], colors[2]);
}
