#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "valid.h"

// Used to determine color of Z-axis based on X-axis and/or Y-axis
unsigned char adjacency[6][4] = {{2,3,4,6},{1,3,5,6},{1,2,4,5},{1,3,5,6},{2,3,4,6},{1,2,4,5}};

// Map of tiles to cubie
int cubie_tiles[20][3] = {
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

void generate_cube(FILE *input, unsigned char *input_cube) {

    // Save the orientation of the cube from the file to a string
    int t;
    int tiles_count = 0;
    char tiles[55];
    while ((t = fgetc(input)) != EOF && tiles_count < 54) {
        if (t != '\n' && t != ' ') {
            tiles[tiles_count] = t;
            tiles_count++;
        }
    }
    tiles[54] = '\0';
    fclose(input);

    // False if there aren't 54 tiles
    if (tiles_count != 54) {
        return_false();
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
            return_false();
        }
    }

    // Store cube
    for (unsigned long i = 0; i < LEN(cubie_tiles); i++) {
        input_cube[i] = set_cubie_colors(tile_color(tiles[cubie_tiles[i][0]]), tile_color(tiles[cubie_tiles[i][1]]), tile_color(tiles[cubie_tiles[i][2]]));
    }

    validate(input_cube);
}

void validate(unsigned char *input_cube) {
    // Create array of indices for permutation parity test
    int perm_cube[20];
    unsigned char input_goal;
    for (unsigned long i = 0; i < LEN(perm_cube); i++) {
        input_goal = calc_goal_value(input_cube[i]);
        for (unsigned long j = 0; j < LEN(goal_state); j++) {
            if (input_goal == goal_state[j]) {
                perm_cube[i] = j;
                break;
            }
        }
    }

    // Count inversions in the array of indices
    int total_inversions = 0;
    for (unsigned long i = 0; i < LEN(perm_cube) - 1; i++) {
        for (unsigned long j = i + 1; j < LEN(perm_cube); j++) {
            if (perm_cube[i] > perm_cube[j]) {
                total_inversions++;
            }
        }
    }
    // Return false if odd number of inversions
    if (total_inversions % 2 != 0) {
        return_false();
    }

    // Count rotations of corner cubies
    int corner_cubies[8] = {0,2,5,7,12,14,17,19};
    int total_rotations = 0;
    for (int i = 0; i < 8; i++) {
        total_rotations += calc_rotations(corner_cubies[i], input_cube[corner_cubies[i]]);
    }
    // Return false if number of rotations not divisible by 3
    if (total_rotations % 3 != 0) {
        return_false();
    }

    // Count the number of incorrectly oriented edge cubies
    int edge_cubies[12] = {1,3,4,6,8,9,10,11,13,15,16,18};
    int incorrect_orientations = 0;
    for (int i = 0; i < 12; i++) {
        incorrect_orientations += calc_orientation(edge_cubies[i], input_cube[edge_cubies[i]]);
    }

    if (incorrect_orientations % 2 != 0) {
        printf("Total incorrect orientations: %d\n", incorrect_orientations);
        return_false();
    }
}

// Function for exiting upon discovery of invalid cube
void return_false() {
    printf("false\n");
    exit(0);
}

// Function to determine color of tile
unsigned char tile_color(char t) {
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

unsigned char z2_tile_color(unsigned char x, unsigned char y, unsigned char z) {
    unsigned char possible[2];
    int possible_used = 0;
    int i = 0;
    int j = 0;
    int length = LEN(adjacency[0]);
    while (i < length && j < length) {
        if (adjacency[x-1][i] == adjacency[y-1][j]) {
            possible[possible_used] = adjacency[x-1][i];
            possible_used++;
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

unsigned char z4_tile_color(unsigned char other, unsigned char z) {
    for (unsigned long i = 0; i < LEN(adjacency[0]); i++) {
        if (adjacency[other-1][i] == z) {
            return i;
        }
    }
    return 4;
}

unsigned char set_cubie_colors(unsigned char x, unsigned char y, unsigned char z) {
    if (x == 0) {
        z = z4_tile_color(y, z);
    } else if (y == 0) {
        z = z4_tile_color(x, z);
    } else if (z != 0) {
        z = z2_tile_color(x, y, z);
    }
    return (x << 5) + (y << 2) + z;
}

void get_cubie_colors(unsigned char cubie, unsigned char *colors) {
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

unsigned char calc_goal_value(unsigned char cubie) {
    unsigned char x_color = 0;
    unsigned char y_color = 0;
    unsigned char z_color = 0;

    unsigned char colors[3];
    get_cubie_colors(cubie, colors);

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
        z_color = z4_tile_color(y_color, z_color);
    } else if (y_color == 0) {
        z_color = z4_tile_color(x_color, z_color);
    } else if (z_color != 0) {
        z_color = z2_tile_color(x_color, y_color, z_color);
    }

    return (x_color << 5) + (y_color << 2) + z_color;
}

int calc_rotations(int index, unsigned char cubie) {
    unsigned char colors[3];
    get_cubie_colors(cubie, colors);

    int x_tile;
    for (int i = 0; i < 3; i++) {
        if ((cubie_tiles[index][i] >= 9 && cubie_tiles[index][i] <= 17) || (cubie_tiles[index][i] >= 27 && cubie_tiles[index][i] <= 35)) {
            x_tile = cubie_tiles[index][i];
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

int calc_orientation(int index, unsigned char cubie)  {
    unsigned char colors[3];
    get_cubie_colors(cubie, colors);

    int x_tile = 54;
    int y_tile = 54;
    int z_tile = 54;
    for (int i = 0; i < 3; i++) {
        if (colors[i] == 2 || colors[i] == 4) {
            x_tile = cubie_tiles[index][i];
            continue;
        } else if (colors[i] == 1 || colors[i] == 5) {
            y_tile = cubie_tiles[index][i];
            continue;
        } else if (colors[i] == 3 || colors[i] == 6) {
            z_tile = cubie_tiles[index][i];
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
