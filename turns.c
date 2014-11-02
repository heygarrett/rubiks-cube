#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "turns.h"

void turnRed(unsigned char *cube) {
    int temp = cube[0];
    cube[0] = cube[5];
    cube[5] = cube[7];
    cube[7] = cube[2];
    cube[2] = temp;
    temp = cube[1];
    cube[1] = cube[3];
    cube[3] = cube[6];
    cube[6] = cube[4];
    cube[4] = temp;
}

void turnGreen(unsigned char *cube) {
    int temp = cube[0];
    cube[0] = cube[12];
    cube[12] = cube[17];
    cube[17] = cube[7];
    cube[6] = temp;
    temp = cube[3];
    cube[3] = cube[8];
    cube[8] = cube[15];
    cube[15] = cube[10];
    cube[10] = temp;
}

void turnYellow(unsigned char *cube) {
    int temp = cube[5];
    cube[5] = cube[17];
    cube[17] = cube[19];
    cube[19] = cube[7];
    cube[7] = temp;
    temp = cube[6];
    cube[6] = cube[10];
    cube[10] = cube[18];
    cube[18] = cube[11];
    cube[11] = temp;
}

void turnBlue(unsigned char *cube) {
    int temp = cube[7];
    cube[7] = cube[19];
    cube[19] = cube[14];
    cube[14] = cube[2];
    cube[2] = temp;
    temp = cube[4];
    cube[4] = cube[11];
    cube[11] = cube[16];
    cube[16] = cube[9];
    cube[9] = temp;
}

void turnOrange(unsigned char *cube) {
    int temp = cube[17];
    cube[17] = cube[12];
    cube[12] = cube[14];
    cube[14] = cube[19];
    cube[19] = temp;
    temp = cube[18];
    cube[18] = cube[15];
    cube[15] = cube[13];
    cube[13] = cube[16];
    cube[16] = temp;
}

void turnWhite(unsigned char *cube) {
    int temp = cube[0];
    cube[0] = cube[3];
    cube[3] = cube[14];
    cube[14] = cube[12];
    cube[12] = temp;
    temp = cube[1];
    cube[1] = cube[9];
    cube[9] = cube[13];
    cube[13] = cube[8];
    cube[8] = temp;
}

// unsigned char switchColors(unsigned char cubie) {
// 
// }
