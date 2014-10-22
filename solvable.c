#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "solvable.h"

#define LEN(a) sizeof(a) / sizeof(a[0])

// Globals
// Used to determine color of Z-axis based on X-axis and/or Y-axis
unsigned char adjacency[6][4] = {{2,3,4,6},{1,3,5,6},{1,2,4,5},{1,3,5,6},{2,3,4,6},{1,2,4,5}};
// Solved cube
unsigned char goalState[20] = {70,7,134,68,132,69,5,133,67,131,65,129,86,23,150,84,148,85,21,149};

int main(int argc, char *argv[]) {

    // Check for a passed file
    if (argc != 2) {
        returnFalse();
    } 

    // Read file in
    FILE *input = fopen(argv[1], "r");
    // Make sure the file can be opened
    if (input == 0) {
        returnFalse();
    }
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
    for (int i = 0; i < tilesCount; i++) {
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
    for (int i= 0; i < LEN(colors); i++) {
        if (colors[i] != 9) {
            returnFalse();
        }
    }

    int cubieTiles[20][3] = {
        // 1
        {9, 0, 51},
        // 2
        {-1, 1, 52},
        // 3
        {17, 2, 53},
        // 4
        {10, 3, -1},
        // 5
        {16, 5, -1},
        // 6
        {11, 6, 12},
        // 7
        {-1, 7, 13},
        // 8
        {15, 8, 14},
        // 9
        {18, -1, 48},
        // 10
        {26, -1, 50},
        // 11
        {20, -1, 21},
        // 12
        {24, -1, 23},
        // 13
        {27, 42, 45},
        // 14
        {-1, 43, 46},
        // 15
        {35, 44, 47},
        // 16
        {28, 39, -1},
        // 17 
        {34, 41, -1},
        // 18
        {29, 36, 30},
        // 19
        {-1, 37, 31},
        // 20
        {33, 38, 32}
    };

    unsigned char inputCube[20];
    for (int i = 0; i < LEN(cubieTiles); i++) {
        inputCube[i] = generateCube(tiles, cubieTiles[i][0], cubieTiles[i][1], cubieTiles[i][2]);
    }
}

// Function for exiting upon discovery of invalid cube
void returnFalse() {
    printf("false\n");
    exit(0);
}

// Function for exiting upon proof of valid cube
void returnTrue() {
    printf("true\n");
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
    for (unsigned char i = 0; i < LEN(adjacency[0]); i++) {
        if (adjacency[other-1][i] == z) {
            return i;
        }
    }
    return 4;
}

unsigned char generateCube(char tiles[], int x, int y, int z) {
    unsigned char x_color = tileColor(tiles[x]);
    unsigned char y_color = tileColor(tiles[y]);
    unsigned char z_color = tileColor(tiles[z]);
    if (x == -1) {
        z_color = z4TileColor(y_color, z_color);
    } else if (y == -1) {
        z_color = z4TileColor(x_color, z_color);
    } else if (z_color != 0) {
        z_color = z2TileColor(x_color, y_color, z_color);
    }
    return (x_color << 5) + (y_color << 2) + z_color;
}
