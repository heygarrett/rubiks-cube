#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tables.h"
#include "turns.h"
#include "valid.h"

void bf_search(struct state root) {
    int depth = 0;
    struct list frontier;
    frontier.size = 1;
    frontier.cubes = malloc(sizeof(struct state));
    frontier.cubes[0] = root;
    struct list new_frontier;
    int total;
    unsigned char *hash_corners = malloc(sizeof(unsigned char) * 88179840);
    for (unsigned long i = 0; i < 88179840; i++) {
        hash_corners[i] = 21;
    }
    unsigned char *hash_edges1 = malloc(sizeof(unsigned char) * 23040);
    for (unsigned long i = 0; i < 23040; i++) {
        hash_edges1[i] = 21;
    }
    unsigned char *hash_edges2 = malloc(sizeof(unsigned char) * 23040);
    for (unsigned long i = 0; i < 23040; i++) {
        hash_edges2[i] = 21;
    }
    unsigned char *hash_table[3] = {hash_corners, hash_edges1, hash_edges2};

    for ( ; ; ) {
        depth++;
        new_frontier.cubes = NULL;
        total = 0;
        for (int i = 0; i < frontier.size; i++) {
            total += create_children(frontier.cubes[i], &new_frontier, total, depth, hash_table);
        }
        new_frontier.size = total;
        free(frontier.cubes);
        frontier = new_frontier;
        printf("Depth %d: %d\n", depth, frontier.size);
        if (frontier.size == 0) {
            break;
        }
    }
    free(frontier.cubes);
    free(new_frontier.cubes);
    free(hash_table[0]);
    free(hash_table[1]);
    free(hash_table[2]);

    unsigned char *compressed_corners = malloc(sizeof(unsigned char) * 44089920);
    for (int i = 0; i < 88179840; i++) {
        if (i % 2 == 0) {
            compressed_corners[i/2] = hash_table[0][i] >> 4;
            compressed_corners[i/2] = compressed_corners[i/2] << 4;
        } else {
            hash_table[0][i] = hash_table[0][i] << 4;
            compressed_corners[i/2] += (hash_table[0][i] >> 4);
        }
    }
    FILE *corner_file = fopen("corners", "wb");
    fwrite(compressed_corners, 1, 44089920, corner_file);
    free(compressed_corners);

    unsigned char *compressed_edges1 = malloc(sizeof(unsigned char) * 11520);
    for (int i = 0; i < 23040; i++) {
        if (i % 2 == 0) {
            compressed_edges1[i/2] = hash_table[1][i] >> 4;
            compressed_edges1[i/2] = compressed_edges1[i/2] << 4;
        } else {
            hash_table[1][i] = hash_table[1][i] << 4;
            compressed_edges1[i/2] += (hash_table[1][i] >> 4);
        }
    }
    FILE *edges1_file = fopen("edges1", "wb");
    fwrite(compressed_corners, 1, 11520, edges1_file);
    free(compressed_edges1);

    unsigned char *compressed_edges2 = malloc(sizeof(unsigned char) * 11520);
    for (int i = 0; i < 23040; i++) {
        if (i % 2 == 0) {
            compressed_edges2[i/2] = hash_table[2][i] >> 4;
            compressed_edges2[i/2] = compressed_edges2[i/2] << 4;
        } else {
            hash_table[2][i] = hash_table[2][i] << 4;
            compressed_edges2[i/2] += (hash_table[2][i] >> 4);
        }
    }
    FILE *edges2_file = fopen("edges2", "wb");
    fwrite(compressed_corners, 1, 11520, edges2_file);
    free(compressed_edges2);
}

int create_children(struct state node, struct list *new_frontier, int node_number, int depth, unsigned char **hash_table) {
    int count = 0;
    if (node.last_face != 'R' && node.last_face != 'O') {
        for (int i = 1; i <= 3; i++) {
            struct state red_cube = node;
            make_move(red_cube.cube, 'R', i);
            red_cube.last_face = 'R';
            if (hash(red_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = red_cube;
            }
        }
    }
    if (node.last_face != 'G' && node.last_face != 'B') {
        for (int i = 1; i <= 3; i++) {
            struct state green_cube = node;
            make_move(green_cube.cube, 'G', i);
            green_cube.last_face = 'G';
            if (hash(green_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = green_cube;
            }
        }
    }
    if (node.last_face != 'Y' && node.last_face != 'W') {
        for (int i = 1; i <= 3; i++) {
            struct state yellow_cube = node;
            make_move(yellow_cube.cube, 'Y', i);
            yellow_cube.last_face = 'Y';
            if (hash(yellow_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = yellow_cube;
            }
        }
    }
    if (node.last_face != 'B') {
        for (int i = 1; i <= 3; i++) {
            struct state blue_cube = node;
            make_move(blue_cube.cube, 'B', i);
            blue_cube.last_face = 'B';
            if (hash(blue_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = blue_cube;
            }
        }
    }
    if (node.last_face != 'O') {
        for (int i = 1; i <= 3; i++) {
            struct state orange_cube = node;
            make_move(orange_cube.cube, 'O', i);
            orange_cube.last_face = 'O';
            if (hash(orange_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = orange_cube;
            }
        }
    }
    if (node.last_face != 'W') {
        for (int i = 1; i <= 3; i++) {
            struct state white_cube = node;
            make_move(white_cube.cube, 'W', i);
            white_cube.last_face = 'W';
            if (hash(white_cube, depth, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = white_cube;
            }
        }
    }

    return count;
}

int hash(struct state node, int depth, unsigned char **hash_table) {
    int indices[3];
    enumerate(node.cube, indices);
    if (hash_table[0][indices[0]] != 21 && hash_table[1][indices[1]] != 21 && hash_table[2][indices[2]] != 21) {
        return 0;
    } else {
        if (hash_table[0][indices[0]] == 21) {
            hash_table[0][indices[0]] = depth;
        }
        if (hash_table[1][indices[1]] == 21) {
            hash_table[1][indices[1]] = depth;
        }
        if (hash_table[2][indices[2]] == 21) {
            hash_table[2][indices[2]] = depth;
        }
        return 1;
    }
}

void enumerate(unsigned char *cube, int *indices) {
    int corners_indices[8];
    int corners_count = 0;
    int edges1_indices[6];
    int edges1_count = 0;
    int edges2_indices[6];
    int edges2_count = 0;

    for (int i = 0; i < 20; i++) {
        if (i == 0 || i == 2 || i == 5 || i == 7 || i == 12 || i == 14 || i == 17 || i == 19) {
            corners_indices[corners_count] = calc_goal_value(cube[i]);
            corners_count++;
        } else if (i == 1 || i == 3 || i == 4 || i == 6 || i == 8 || i == 9) {
            edges1_indices[edges1_count] = calc_goal_value(cube[i]);
            edges1_count++;
        } else if (i == 10 || i == 11 || i == 13 || i == 15 || i == 16 || i == 18) {
            edges2_indices[edges2_count] = calc_goal_value(cube[i]);
            edges2_count++;
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 20; j++) {
            if (corners_indices[i] == goal_state[j]) {
                corners_indices[i] = j;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 20; j++) {
            if (edges1_indices[i] == goal_state[j]) {
                edges1_indices[i] = j;
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 20; j++) {
            if (edges2_indices[i] == goal_state[j]) {
                edges2_indices[i] = j;
            }
        }
    }

    int multi_base[14];
    int multi_marker = 13;
    for (int i = 0; i < 8; i++) {
        int count = 0;
        for (int j = i; j < 8; j++) {
            if (corners_indices[i] > corners_indices[j]) {
                count++;
            }
        }
        multi_base[multi_marker] = count;
        --multi_marker;
    }
    int corners[8] = {0, 2, 5, 7, 12, 14, 17, 19};
    for (int i = 0; i < 7; i++) {
        multi_base[i] = calc_rotations(corners[i], cube[corners[i]]);
    }

    indices[0] = ((((((((((((((multi_base[0])*3+multi_base[1])*3+multi_base[2])*3+multi_base[3])*3+multi_base[4])*3+multi_base[5])*3+multi_base[6])*2+multi_base[7])*3+multi_base[8])*4+multi_base[9])*5+multi_base[10])*6+multi_base[11])*7+multi_base[12])*8+multi_base[13]);

    multi_marker = 9;
    for (int i = 0; i < 6; i++) {
        int count = 0;
        for (int j = i; j < 6; j++) {
            if (edges1_indices[i] > edges1_indices[j]) {
                count++;
            }
        }
        multi_base[multi_marker] = count;
        --multi_marker;
    }
    int edges1[6] = {1, 3, 4, 6, 8, 9};
    for (int i = 0; i < 5; i++) {
        multi_base[i] = calc_orientation(edges1[i], cube[edges1[i]]);
    }

    indices[1] = ((((((((((multi_base[0])*2+multi_base[1])*2+multi_base[2])*2+multi_base[3])*2+multi_base[4])*2+multi_base[5])*3+multi_base[6])*4+multi_base[7])*5+multi_base[8])*6+multi_base[9]);

    multi_marker = 9;
    for (int i = 0; i < 6; i++) {
        int count = 0;
        for (int j = i; j < 6; j++) {
            if (edges2_indices[i] > edges2_indices[j]) {
                count++;
            }
        }
        multi_base[multi_marker] = count;
        --multi_marker;
    }
    int edges2[6] = {10, 11, 13, 15, 16, 18};
    for (int i = 0; i < 5; i++) {
        multi_base[i] = calc_orientation(edges2[i], cube[edges2[i]]);
    }

    indices[2] = ((((((((((multi_base[0])*2+multi_base[1])*2+multi_base[2])*2+multi_base[3])*2+multi_base[4])*2+multi_base[5])*3+multi_base[6])*4+multi_base[7])*5+multi_base[8])*6+multi_base[9]);
}
