#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "valid.h"

#define LEN(a) (sizeof(a)) / (sizeof(a[0]))

// Globals
// Used to determine color of Z-axis based on X-axis and/or Y-axis
unsigned char adjacency[6][4] = {{2,3,4,6},{1,3,5,6},{1,2,4,5},{1,3,5,6},{2,3,4,6},{1,2,4,5}};
// Solved cube
unsigned char goalState[20] = {70,7,134,68,132,69,5,133,67,131,65,129,86,23,150,84,148,85,21,149};

// Map of tiles to cubie
int cubieTiles[20][3] = {
    // 1
    {9, 0, 51},
    // 2
    {54, 1, 52},
    // 3
    {17, 2, 53},
    // 4
    {10, 3, 54},
    // 5
    {16, 5, 54},
    // 6
    {11, 6, 12},
    // 7
    {54, 7, 13},
    // 8
    {15, 8, 14},
    // 9
    {18, 54, 48},
    // 10
    {26, 54, 50},
    // 11
    {20, 54, 21},
    // 12
    {24, 54, 23},
    // 13
    {27, 42, 45},
    // 14
    {54, 43, 46},
    // 15
    {35, 44, 47},
    // 16
    {28, 39, 54},
    // 17 
    {34, 41, 54},
    // 18
    {29, 36, 30},
    // 19
    {54, 37, 31},
    // 20
    {33, 38, 32}
};

void generateCube(FILE *input, unsigned char *inputCube) {

    // Save the orientation of the cube from the file to a string
    int t;
    int tilesCount = 0;
    char tiles[55];
    while ((t = fgetc(input)) != EOF && tilesCount < 54) {
        if (t != '\n' && t != ' ') {
            tiles[tilesCount] = t;
            tilesCount++;
        }
    }
    tiles[54] = '\0';
    fclose(input);

    // False if there aren't 54 tiles
    if (tilesCount != 54) {
        returnFalse();
    }
    // False if there aren't 9 tiles of each color
    int colors[6] = {0, 0, 0, 0, 0, 0};
    for (unsigned long i = 0; i < LEN(tiles); i++) {
        if (tiles[i] == 'R') {
            colors[0] += 1;
        } else if (tiles[i] == 'Y') {
            colors[1] += 1;
        } else if (tiles[i] == 'B') {
            colors[2] += 1;
        } else if (tiles[i] == 'O') {
            colors[3] += 1;
        } else if (tiles[i] == 'W') {
            colors[4] += 1;
        } else if (tiles[i] == 'G') {
            colors[5] += 1;
        }
    }
    for (unsigned long i = 0; i < LEN(colors); i++) {
        if (colors[i] != 9) {
            returnFalse();
        }
    }

    // Store cube
    for (unsigned long i = 0; i < LEN(cubieTiles); i++) {
        inputCube[i] = setCubieColors(tileColor(tiles[cubieTiles[i][0]]), tileColor(tiles[cubieTiles[i][1]]), tileColor(tiles[cubieTiles[i][2]]));
    }

    validate(inputCube);
}

void validate(unsigned char *inputCube) {
    // Create array of indices for permutation parity test
    int permCube[20];
    unsigned char inputGoal;
    for (unsigned long i = 0; i < LEN(permCube); i++) {
        inputGoal = calcGoalValue(inputCube[i]);
        for (unsigned long j = 0; j < LEN(goalState); j++) {
            if (inputGoal == goalState[j]) {
                permCube[i] = j;
                break;
            }
        }
    }

    // Count inversions in the array of indices
    int totalInversions = 0;
    for (unsigned long i = 0; i < LEN(permCube) - 1; i++) {
        for (unsigned long j = i + 1; j < LEN(permCube); j++) {
            if (permCube[i] > permCube[j]) {
                totalInversions++;
            }
        }
    }
    // Return false if odd number of inversions
    if (totalInversions % 2 != 0) {
        returnFalse();
    }

    // Count rotations of corner cubies
    int cornerCubies[8] = {0,2,5,7,12,14,17,19};
    int totalRotations = 0;
    for (int i = 0; i < 8; i++) {
        totalRotations += calcRotations(cornerCubies[i], inputCube[cornerCubies[i]]);
    }
    // Return false if number of rotations not divisible by 3
    if (totalRotations % 3 != 0) {
        returnFalse();
    }

    // Count the number of incorrectly oriented edge cubies
    int edgeCubies[12] = {1,3,4,6,8,9,10,11,13,15,16,18};
    int incorrectOrientations = 0;
    for (int i = 0; i < 12; i++) {
        incorrectOrientations += calcOrientation(edgeCubies[i], inputCube[edgeCubies[i]]);
    }

    if (incorrectOrientations % 2 != 0) {
        printf("Total incorrect orientations: %d\n", incorrectOrientations);
        returnFalse();
    }
}

// Function for exiting upon discovery of invalid cube
void returnFalse() {
    printf("false\n");
    exit(0);
}

// Function to determine color of tile
unsigned char tileColor(char t) {
    if (t == 'R') {
        return (unsigned char) 1;
    } else if (t == 'G') {
        return (unsigned char) 2;
    } else if (t == 'Y') {
        return (unsigned char) 3;
    } else if (t == 'B') {
        return (unsigned char) 4;
    } else if (t == 'O') {
        return (unsigned char) 5;
    } else if (t == 'W') {
        return (unsigned char) 6;
    } else {
        return (unsigned char) 0;
    }
}

unsigned char z2TileColor(unsigned char x, unsigned char y, unsigned char z) {
    unsigned char possible[2];
    int possibleUsed = 0;
    int i = 0;
    int j = 0;
    int length = LEN(adjacency[0]);
    while (i < length && j < length) {
        if (adjacency[x-1][i] == adjacency[y-1][j]) {
            possible[possibleUsed] = adjacency[x-1][i];
            possibleUsed++;
            i++;
            j++;
        } else if (adjacency[x-1][i] < adjacency[y-1][j]) {
            i++;
        } else {
            j++;
        }
    }
    if (z == possible[0]) {
        return 1;
    } else {
        return 2;
    }
}

unsigned char z4TileColor(unsigned char other, unsigned char z) {
    for (unsigned long i = 0; i < LEN(adjacency[0]); i++) {
        if (adjacency[other-1][i] == z) {
            return i;
        }
    }
    return 4;
}

unsigned char setCubieColors(unsigned char x, unsigned char y, unsigned char z) {
    if (x == 0) {
        z = z4TileColor(y, z);
    } else if (y == 0) {
        z = z4TileColor(x, z);
    } else if (z != 0) {
        z = z2TileColor(x, y, z);
    }
    return (x << 5) + (y << 2) + z;
}

void getCubieColors(unsigned char cubie, unsigned char *colors) {
    colors[0] = cubie >> 5; 
    colors[1] = cubie << 3;
    colors[1] = colors[1] >> 5;
    colors[2] =  cubie << 6;
    colors[2] = colors[2] >> 6;

    // Find third color
    if (colors[0] == 0) {
        colors[2] = adjacency[colors[1] - 1][colors[2]];
    } else if (colors[1] == 0) {
        colors[2] = adjacency[colors[0] - 1][colors[2]];
    } else if (colors[2] != 0) {
        int count = 0;
        unsigned char common[2];
        for (unsigned long i = 0; i < LEN(adjacency[0]); i++) {
            for (unsigned long j = 0; j < LEN(adjacency[0]); j++) {
                if (adjacency[colors[0] - 1][i] == adjacency[colors[1] - 1][j]) {
                    common[count] = adjacency[colors[0] - 1][i];
                    count++;
                }
            }
        }
        if (colors[2] == 1) {
            colors[2] = common[0];
        } else {
            colors[2] = common[1];
        }
    }
}

unsigned char calcGoalValue(unsigned char cubie) {
    unsigned char x_color = 0;
    unsigned char y_color = 0;
    unsigned char z_color = 0;

    unsigned char colors[3];
    getCubieColors(cubie, colors);

    // Rearrange colors to goal state orientation
    for (unsigned long i = 0; i < LEN(colors); i++) {
        if (colors[i] == 2 || colors[i] == 4) {
            x_color = colors[i];
        } else if (colors[i] == 1 || colors[i] == 5) {
            y_color = colors[i];
        } else if (colors[i] == 3 || colors[i] == 6) {
            z_color = colors[i];
        }
    }

    // Calculate z-axis value
    if (x_color == 0) {
        z_color = z4TileColor(y_color, z_color);
    } else if (y_color == 0) {
        z_color = z4TileColor(x_color, z_color);
    } else if (z_color != 0) {
        z_color = z2TileColor(x_color, y_color, z_color);
    }

    return (x_color << 5) + (y_color << 2) + z_color;
}

int calcRotations(int index, unsigned char cubie) {
    unsigned char colors[3];
    getCubieColors(cubie, colors);

    int x_tile;
    for (int i = 0; i < 3; i++) {
        if ((cubieTiles[index][i] >= 9 && cubieTiles[index][i] <= 17) || (cubieTiles[index][i] >= 27 && cubieTiles[index][i] <= 35)) {
            x_tile = cubieTiles[index][i];
            break;
        }
    }
    int rotations = 0;
    char temp;
    if (index == 0 || index == 7 || index == 14 || index == 17) {
        for (int i = 0; i < 3; i++) {
            if (colors[0] == 2 || colors[0] == 4) {
                break;
            }
            temp = colors[0];
            colors[0] = colors[1];
            colors[1] = colors[2];
            colors[2] = temp;
            rotations++;
        }
    } else {
        for (int i = 0; i < 3; i++) {
            if (colors[0] == 2 || colors[0] == 4) {
                break;
            }
            temp = colors[2];
            colors[2] = colors[1];
            colors[1] = colors[0];
            colors[0] = temp;
            rotations++;
        }
    }
        
    return rotations;
}

int calcOrientation(int index, unsigned char cubie)  {
    unsigned char colors[3];
    getCubieColors(cubie, colors);

    int x_tile = 54;
    int y_tile = 54;
    int z_tile = 54;
    for (int i = 0; i < 3; i++) {
        if (colors[i] == 2 || colors[i] == 4) {
            x_tile = cubieTiles[index][i];
            continue;
        } else if (colors[i] == 1 || colors[i] == 5) {
            y_tile = cubieTiles[index][i];
            continue;
        } else if (colors[i] == 3 || colors[i] == 6) {
            z_tile = cubieTiles[index][i];
            continue;
        }
    }

    if (x_tile != 54) {
        if ((x_tile >= 0 && x_tile <= 8) || (x_tile >= 36 && x_tile <= 44) || (x_tile >= 21 && x_tile <= 23) || (x_tile >= 48 && x_tile <= 50)) {
            return 1;
        }
    } else if (!((y_tile >= 0 && y_tile <= 8) || (y_tile >= 36 && y_tile <= 44))) {
        if (!((z_tile >= 9 && z_tile <= 11) || (z_tile >= 15 && z_tile <= 20) || (z_tile >= 24 && z_tile <= 29) || (z_tile >= 33 && z_tile <= 35))) {
            return 1;
        }
    }

    return 0;
}
