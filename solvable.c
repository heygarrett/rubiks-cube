#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definitions
#define GOAL "RRRRRRRRRYYYYYYYYYBBBBBBBBBOOOOOOOOOWWWWWWWWWGGGGGGGGG"
char xcoor[54] = {0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,0,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0};
char ycoor[54] = {0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,0,0,0,1,1,1,2,2,2,2,1,0,2,1,0,2,1,0};
char zcoor[54] = {0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2};

// Prototypes
void returnFalse();
void returnTrue();
char * findConnectedTile(int x, int y, int z);
void findHome(char * connectedTiles, int result[]);

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
    int c;
    int count = 0;
    char cube[55] = {'\0'};
    while ((c = fgetc(input)) != EOF && count < 54) {
        if (c != '\n' && c != ' ') {
            cube[count] = c;
            count++;
        }
    }
    fclose(input);

    // False if there aren't 54 tiles
    if (strlen(cube) != 54) {
        returnFalse();
    }
    // False if there aren't 9 tiles of each color
    int colors[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < strlen(cube); i++) {
        if (cube[i] == 'R') {
            colors[0] += 1;
            if (colors[0] > 9) {
                returnFalse();
            }
        } else if (cube[i] == 'Y') {
            colors[1] += 1;
            if (colors[1] > 9) {
                returnFalse();
            }
        } else if (cube[i] == 'B') {
            colors[2] += 1;
            if (colors[2] > 9) {
                returnFalse();
            }
        } else if (cube[i] == 'O') {
            colors[3] += 1;
            if (colors[3] > 9) {
                returnFalse();
            }
        } else if (cube[i] == 'W') {
            colors[4] += 1;
            if (colors[4] > 9) {
                returnFalse();
            }
        } else if (cube[i] == 'G') {
            colors[5] += 1;
            if (colors[5] > 9) {
                returnFalse();
            }
        }
    }

    // Rearrange the string for simplicity
    char temp[3];
    memcpy(temp, &(cube[9]), 3);
    memmove(&(cube[9]), &(cube[12]), strlen(cube) - 12);
    memcpy(&(cube[strlen(cube) - 3]), temp, 3);

    memcpy(temp, &(cube[15]), 3);
    memmove(&(cube[15]), &(cube[18]), strlen(cube) - 18);
    memcpy(&(cube[strlen(cube) - 3]), temp, 3);

    memcpy(temp, &(cube[21]), 3);
    memmove(&(cube[21]), &(cube[24]), strlen(cube) - 24);
    memcpy(&(cube[strlen(cube) - 3]), temp, 3);

    memcpy(temp, &(cube[15]), 3);
    memmove(&(cube[15]), &(cube[12]), 3);
    memcpy(&(cube[12]), temp, 3);

    memcpy(temp, &(cube[21]), 3);
    memmove(&(cube[18]), &(cube[15]), 6);
    memcpy(&(cube[15]), temp, 3);

    // Check to see if input is in goal state
    if (strcmp(cube, GOAL) == 0) {
        returnTrue();
    }

    // Test for permutation parity
    char currentTile;
    char connectedTiles[3];
    int home[3];
    int result;
    for (int i = 0; i < 54; i++) {
        currentTile = cube[i];
        if (currentTile != 'F') {
            memcpy(connectedTiles, findConnectedTile(xcoor[i], ycoor[i], zcoor[i]), 2);
            findHome(connectedTiles, home);
            result = (home[0] - xcoor[0]) + (home[1] - ycoor[1]) + (home[2] - zcoor[2]);
            if (result % 2 != 0) {
                returnFalse();
            }
        }
    }

    returnTrue();
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

// Function for finding the connected tiles and thus the correct cubie
char * findConnectedTile(int x, int y, int z) {
    int count = 0;
    static char coordinates[3];
    for (int a = 0; a < 54; a++) {
        for (int b = 0; b < 54; b++) {
            for (int c = 0; c < 54; c++) {
                if (a == b && b == c && xcoor[a] == x && ycoor[b] == y && zcoor[c] == z) {
                    coordinates[count] = GOAL[a];
                    count++;
                }
            }
        }
    }
    return coordinates;
}

// Function for finding the goal state location of the cubie
void findHome(char * connectedTiles, int home[]) {
    if (sizeof(connectedTiles)/sizeof(connectedTiles[0]) < 3) {
        for (int a = 0; a < 54; a++) {
            for (int b = 0; b < 54; b++) {
                if (GOAL[a] == connectedTiles[0] && GOAL[b] == connectedTiles[1]) {
                    if(xcoor[a] == xcoor[b] && ycoor[a] == ycoor[b] && zcoor[a] == zcoor[b]) {
                        home[0] = xcoor[a];
                        home[1] = ycoor[a];
                        home[2] = zcoor[a];
                    }
                }
            }
        }
    }
}
