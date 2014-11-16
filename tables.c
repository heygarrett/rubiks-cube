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
    unsigned char *hash_table = malloc(sizeof(unsigned char) * 88179840);
    for (unsigned long i = 0; i < 88179840; i++) {
        hash_table[i] = 21;
    }

    for ( ; ; ) {
        depth++;
        new_frontier.cubes = NULL;
        total = 0;
        for (int i = 0; i < frontier.size; i++) {
            total += create_children(frontier.cubes[i], &new_frontier, total, hash_table);
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
    free(hash_table);
}

int create_children(struct state node, struct list *new_frontier, int node_number, unsigned char *hash_table) {
    int count = 0;
    if (node.last_face != 'R' && node.last_face != 'O') {
        for (int i = 1; i <= 3; i++) {
            struct state red_cube = node;
            make_move(red_cube.cube, 'R', i);
            red_cube.last_face = 'R';
            if (hash(red_cube, hash_table)) {
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
            if (hash(green_cube, hash_table)) {
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
            if (hash(yellow_cube, hash_table)) {
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
            if (hash(blue_cube, hash_table)) {
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
            if (hash(orange_cube, hash_table)) {
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
            if (hash(white_cube, hash_table)) {
                count++;
                new_frontier->cubes = realloc(new_frontier->cubes, (node_number + count) * sizeof(struct state));
                new_frontier->cubes[node_number + count - 1] = white_cube;
            }
        }
    }

    return count;
}

int hash(struct state node, unsigned char *hash_table) {
    unsigned char corners[8] = {0, 2, 5, 7, 12, 14, 17, 19};
    // unsigned char edges1[6] = {1, 3, 4, 6, 8, 9};
    // unsigned char edges2[6] = {10, 11, 13, 15, 16, 18};

    int corner_indices[8];
    for (int i = 0; i < 8; i++) {
        corner_indices[i] = calc_goal_value(node.cube[corners[i]]);
        for (int j = 0; j < 20; j++) {
            if (corner_indices[i] == goal_state[j]) {
                corner_indices[i] = j;
            }
        }
    }
    int multi_base[14];
    int multi_marker = 13;
    for (int i = 0; i < 8; i++) {
        int count = 0;
        for (int j = i; j < 8; j++) {
            if (corner_indices[i] > corner_indices[j]) {
                count++;
            }
        }
        multi_base[multi_marker] = count;
        --multi_marker;
    }
    for (int i = 0; i < 7; i++) {
        multi_base[i] = calc_rotations(corners[i], node.cube[corners[i]]);
    }

    int index = ((((((((((((((multi_base[0])*3+multi_base[1])*3+multi_base[2])*3+multi_base[3])*3+multi_base[4])*3+multi_base[5])*3+multi_base[6])*2+multi_base[7])*3+multi_base[8])*4+multi_base[9])*5+multi_base[10])*6+multi_base[11])*7+multi_base[12])*8+multi_base[13]);


    if (hash_table[index] != 21) {
        return 0;
    } else {
        hash_table[index] = 0;
        return 1;
    }
}
